#include "smpp/smpp_server/smpp_session_handler.h"

#include <sstream>

#include "boost/shared_array.hpp"
#include "smpp/pdu/pdu.h"
#include "smpp/smpp_constants.h"
#include "smpp/smpp_exceptions.h"
#include "smpp/util/logging.h"
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
      [me = shared_from_this(), &commandLengthBuffer](const boost::system::error_code& ec,
                                                      std::size_t length) {
        if (ec) {
          std::stringstream error;
          error << "Error code: " << ec.value() << "; error message: " << ec.message();
          throw TransportException(error.str());
        }

        uint32_t nCommandLength = ntohl(*reinterpret_cast<uint32_t*>(commandLengthBuffer.get()));
        me->readPduAfterCommandLength(nCommandLength);
      });
}

void SmppSessionHandler::readPduAfterCommandLength(uint32_t nCommandLength) {
  INFO << "SmppSessionHandler::readPduAfterCommandLength( " << nCommandLength << ")";
  boost::shared_array<uint8_t> pduBuffer{new uint8_t[nCommandLength - 4]};
  boost::asio::async_read(
      m_socket, boost::asio::buffer(pduBuffer.get(), nCommandLength - 4),
      [&, me = shared_from_this()](boost::system::error_code ec, std::size_t length) {
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
  DEBUG << "SmppSessionHandler::onReceivedPdu() pdu is of type ["
        << util::commandIdToString(pdu->getCommandId()) << "]";
  m_receivePduQueue.push_back(std::move(pdu));

  switch (pdu->getCommandId()) {
    case constants::CMD_ID_BIND_TRANSCEIVER: {
      handleReceivedBindTransmitter(std::move(pdu));
    }
    default: {
    }
  }
}

void SmppSessionHandler::handleReceivedBindTransmitter(Pdu::Ptr pdu) {
  auto bindTransmitterPdu = dynamic_cast<BindTransmitter*>(pdu.get());

  smpp::BindTransmitterResp bindTransmitterRespPdu{
      smpp::builder::BindRespBuilder()
          .withCommandLength(smpp::constants::PDU_HEADER_LENGTH +
                             bindTransmitterRespPdu.getSystemId().size() + 1 + 5)
          .withCommandStatus(smpp::constants::errors::ESME_ROK)
          .withSequenceNumber(bindTransmitterPdu->getSequenceNumber())
          .withSystemId(bindTransmitterPdu->getSystemId())
          .withScInterfaceVersion(bindTransmitterPdu->getInterfaceVersion())};

  Pdu::Ptr ptr;
  ptr.reset(&bindTransmitterRespPdu);
  sendPdu(std::move(ptr));
}

void SmppSessionHandler::sendPdu(Pdu::Ptr pdu) {
  boost::asio::post(m_ioContext, m_writeStrand.wrap([me = shared_from_this(), &pdu] {
    me->queuePdu(std::move(pdu));
  }));
}

void SmppSessionHandler::queuePdu(Pdu::Ptr pdu) {
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
    std::stringstream error;
    error << "Error code: " << ec.value() << "; error message: " << ec.message();
    throw TransportException(error.str());
  }
}

}  // namespace smpp
