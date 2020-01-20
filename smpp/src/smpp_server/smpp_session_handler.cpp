#include "smpp/smpp_server/smpp_session_handler.h"

#include <sstream>

#include "boost/shared_array.hpp"
#include "smpp/pdu/pdu.h"
#include "smpp/smpp_exceptions.h"
#include "smpp/util/serialization_util.h"

namespace smpp {

SmppSessionHandler::SmppSessionHandler(boost::asio::io_context& ioContext)
    : m_ioContext{ioContext}, m_socket{ioContext}, m_writeStrand{ioContext} {}

boost::asio::ip::tcp::socket& SmppSessionHandler::socket() { return m_socket; }

void SmppSessionHandler::start() { readPduCommandLength(); }

void SmppSessionHandler::readPduCommandLength() {
  boost::shared_array<uint8_t> commandLengthBuffer{new uint8_t[4]};
  boost::asio::async_read(m_socket, boost::asio::buffer(commandLengthBuffer.get(), 4),
                          [me = shared_from_this(), &commandLengthBuffer](
                              const boost::system::error_code& ec, std::size_t length) {
                            if (ec) {
                              // smpp::throwTransportExceptionByErrCode(ec);
                            }

                            uint32_t nCommandLength =
                                ntohl(*reinterpret_cast<uint32_t*>(commandLengthBuffer.get()));
                            me->readPdu(nCommandLength);
                          });
}

void SmppSessionHandler::readPdu(uint32_t nCommandLength) {
  boost::shared_array<uint8_t> pduBuffer{new uint8_t[nCommandLength - 4]};
  boost::asio::async_read(m_socket, boost::asio::buffer(pduBuffer.get(), nCommandLength - 4),
                          [&](boost::system::error_code ec, std::size_t length) {
                            if (ec) {
                              // smpp::throwTransportExceptionByErrCode(ec);
                            }

                            std::stringstream ssPdu;
                            binary::serializeInt32(nCommandLength, ssPdu);
                            for (int byte = 0; byte < nCommandLength - 4; byte++) {
                              binary::serializeInt8(pduBuffer[byte], ssPdu);
                            }

                            auto receivedPdu = Pdu::deserialize(ssPdu);

                            // do something with it
                          });
}

void SmppSessionHandler::sendPdu(smpp::Pdu::Ptr pdu) {
  boost::asio::post(m_ioContext, m_writeStrand.wrap([me = shared_from_this(), &pdu] {
    me->queuePdu(std::move(pdu));
  }));
}

void SmppSessionHandler::queuePdu(smpp::Pdu::Ptr pdu) {
  // this is thread safe because of the strand
  const bool bWriteInProgress = !m_sendPduQueue.empty();
  m_sendPduQueue.push_back(std::move(pdu));

  if (!bWriteInProgress) {
    startPduSend();
  }
}

void SmppSessionHandler::startPduSend() {
  std::stringstream sendPduStream;
  m_sendPduQueue.front()->serialize(sendPduStream);
  boost::asio::async_write(
      m_socket, boost::asio::buffer(sendPduStream.str()),
      m_writeStrand.wrap([me = shared_from_this()](const boost::system::error_code& ec,
                                                   std::size_t) { me->pduSendDone(ec); }));
}

void SmppSessionHandler::pduSendDone(const boost::system::error_code& ec) {
  if (!ec) {
    m_sendPduQueue.pop_front();
    if (!m_sendPduQueue.empty()) {
      startPduSend();
    }
  } else {
    // throw transport exception maybe
  }
}

}  // namespace smpp
