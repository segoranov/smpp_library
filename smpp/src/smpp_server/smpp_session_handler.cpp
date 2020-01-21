#include "smpp/smpp_server/smpp_session_handler.h"

#include <sstream>

#include "boost/shared_array.hpp"
#include "smpp/pdu/pdu.h"
#include "smpp/smpp_constants.h"
#include "smpp/smpp_exceptions.h"
#include "smpp/util/logging.h"
#include "smpp/util/print_util.h"
#include "smpp/util/serialization_util.h"

namespace smpp {

SmppSessionHandler::SmppSessionHandler(boost::asio::io_context& ioContext)
    : m_ioContext{ioContext}, m_socket{ioContext}, m_writeStrand{ioContext} {}

boost::asio::ip::tcp::socket& SmppSessionHandler::socket() { return m_socket; }

void SmppSessionHandler::start() {
  m_enSessionState.store(session_util::SessionState::OPEN);
  readPdu();
}

void SmppSessionHandler::readPdu() {
  INFO << "SmppSessionHandler::readPdu()";
  readPduCommandLength();
}

void SmppSessionHandler::readPduCommandLength() {
  INFO << "SmppSessionHandler::readPduCommandLength()";
  boost::shared_array<uint8_t> commandLengthBuffer{new uint8_t[4]};
  boost::asio::async_read(
      m_socket, boost::asio::buffer(commandLengthBuffer.get(), 4),
      [me = shared_from_this(), commandLengthBuffer](const boost::system::error_code& ec,
                                                     std::size_t length) {
        if (ec) {
          std::stringstream error;
          error << "Error code: " << ec.value() << "; error message: " << ec.message();
          throw TransportException(error.str());
        }

        uint32_t* pCommandLength = reinterpret_cast<uint32_t*>(commandLengthBuffer.get());
        uint32_t nCommandLength = ntohl(*pCommandLength);
        INFO << "Parsed command length: " << nCommandLength;
        me->readPduAfterCommandLength(nCommandLength);
      });
}

void SmppSessionHandler::readPduAfterCommandLength(uint32_t nCommandLength) {
  INFO << "SmppSessionHandler::readPduAfterCommandLength(" << nCommandLength << ")";
  boost::shared_array<uint8_t> pduBuffer{new uint8_t[nCommandLength - 4]};
  boost::asio::async_read(
      m_socket, boost::asio::buffer(pduBuffer.get(), nCommandLength - 4),
      [=, me = shared_from_this()](boost::system::error_code ec, std::size_t length) {
        if (ec) {
          std::stringstream error;
          error << "Error code: " << ec.value() << "; error message: " << ec.message();
          throw TransportException(error.str());
        }

        std::stringstream ssPdu;
        binary::serializeInt32(nCommandLength, ssPdu);
        for (int byte = 0; byte < nCommandLength - 4; byte++) {
          binary::serializeInt8(pduBuffer[byte], ssPdu);
        }
        auto receivedPdu = Pdu::deserialize(ssPdu);
        readPdu();
        me->onReceivedPdu(std::move(receivedPdu));
      });
}

void SmppSessionHandler::onReceivedPdu(Pdu::Ptr pdu) {
  INFO << "SmppSessionHandler::onReceivedPdu()";
  DEBUG << "Pdu is of type [" << util::commandIdToString(pdu->getCommandId()) << "]";
  // m_receivePduQueue.push_back(std::move(pdu));

  switch (pdu->getCommandId()) {
    case constants::CMD_ID_BIND_TRANSMITTER: {
      onReceivedBindTransmitter(std::move(pdu));
      break;
    }
    default: {
    }
  }
}

void SmppSessionHandler::onReceivedBindTransmitter(Pdu::Ptr pdu) {
  INFO << "SmppSessionHandler::onReceivedBindTransmitter()";
  auto bindTransmitterPdu = dynamic_cast<BindTransmitter*>(pdu.get());

  DEBUG << "Creating BindTransmitterResp";
  // smpp::BindTransmitterResp bindTransmitterRespPdu{
  //     smpp::builder::BindRespBuilder()
  //         .withCommandStatus(smpp::constants::errors::ESME_ROK)
  //         .withSequenceNumber(bindTransmitterPdu->getSequenceNumber())
  //         .withSystemId(bindTransmitterPdu->getSystemId())
  //         .withScInterfaceVersion(bindTransmitterPdu->getInterfaceVersion())};
  smpp::BindTransmitterResp bindTransmitterRespPdu{
      smpp::builder::BindRespBuilder()
          .withCommandStatus(smpp::constants::errors::ESME_ROK)
          .withSequenceNumber(1)
          .withSystemId("SMPP3TEST")
          .withScInterfaceVersion(smpp::constants::VERSION_5_0)};
  DEBUG << "Created BindTransmitterResp";

  std::stringstream pduBuffer;
  bindTransmitterRespPdu.serialize(pduBuffer);
  sendPdu(pduBuffer.str());
}

void SmppSessionHandler::sendPdu(const std::string& strPdu) {
  INFO << "SmppSessionHandler::sendPdu()";
  boost::asio::post(m_ioContext, m_writeStrand.wrap(
                                     [me = shared_from_this(), strPdu] { me->queuePdu(strPdu); }));
}

void SmppSessionHandler::queuePdu(const std::string& strPdu) {
  INFO << "SmppSessionHandler::queuePdu()";
  // this is thread safe because of the strand
  const bool bWriteInProgress = !m_sendPduQueue.empty();
  m_sendPduQueue.push_back(strPdu);

  if (!bWriteInProgress) {
    startPduSend();
  }
}

void SmppSessionHandler::startPduSend() {
  INFO << "SmppSessionHandler::startPduSend()";
  boost::asio::async_write(
      m_socket, boost::asio::buffer(m_sendPduQueue.front()),
      m_writeStrand.wrap([me = shared_from_this()](const boost::system::error_code& ec,
                                                   std::size_t) { me->pduSendDone(ec); }));
}

void SmppSessionHandler::pduSendDone(const boost::system::error_code& ec) {
  INFO << "SmppSessionHandler::pduSendDone()";
  if (!ec) {
    m_sendPduQueue.pop_front();
    if (!m_sendPduQueue.empty()) {
      startPduSend();
    }
  } else {
    std::stringstream error;
    error << "Error code: " << ec.value() << "; error message: " << ec.message();
    throw TransportException(error.str());
  }
}

}  // namespace smpp
