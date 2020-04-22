#include "smpp/smpp_client.h"

namespace smpp {

SmppClient::SmppClient(std::shared_ptr<TcpSocket> ptrTcpSocket) : m_ptrTcpSocket{ptrTcpSocket} {
  m_enSessionState = session_util::SessionState::OPEN;
}

Pdu::SPtr SmppClient::unbind() {
  // TODO
  return nullptr;
}

Pdu::SPtr SmppClient::sendPduSync(Pdu::SPtr pdu) {
  checkTcpConnection();
  checkTransmissionIsPossible();
  sendPdu(pdu);
  return readPduResponse(pdu->getSequenceNumber(), pdu->getCommandId());
}

void SmppClient::sendPduAsync(Pdu::SPtr pdu) {
  checkTcpConnection();
  checkTransmissionIsPossible();

  boost::asio::streambuf buff;
  std::ostream os(&buff);
  pdu->serialize(os);

  boost::asio::async_write(*m_ptrTcpSocket, buff.data(),
                           [this](boost::system::error_code ec, std::size_t s) {
                             if (ec) {
                               std::cout << "Could not send PDU to server. Bytes sent - " << s
                                         << ". " << ec.value() << ":" << ec.message() << std::endl;
                             }
                           });
}

void SmppClient::checkTransmissionIsPossible() const {
  if (m_enSessionState == session_util::SessionState::BOUND_RX) {
    throw InvalidSessionStateException("Trying to send a PDU in BOUND_RX state");
  }

  if (m_enSessionState != session_util::SessionState::BOUND_TRX &&
      m_enSessionState != session_util::SessionState::BOUND_TX) {
    throw InvalidSessionStateException("Trying to send a PDU in non-bound state");
  }
}

void SmppClient::sendPdu(Pdu::SPtr pdu) {
  boost::asio::streambuf buff;
  std::ostream os(&buff);
  pdu->serialize(os);

  boost::system::error_code ec;
  boost::asio::write(*m_ptrTcpSocket, buff.data(), ec);

  if (ec) {
    // TODO handle writing error
    return;
  }
}

Pdu::SPtr SmppClient::readPduResponse(uint32_t nSequenceNumber, uint32_t nCommandId) {
  const uint32_t nResponseCommandId = constants::CMD_ID_GENERIC_NACK | nCommandId;

  auto it = m_pduResponseQueue.begin();
  while (it != m_pduResponseQueue.end()) {
    auto pdu = *it;
    if (pdu->getSequenceNumber() == nSequenceNumber && pdu->getCommandId() == nResponseCommandId) {
      m_pduResponseQueue.erase(it);
      return pdu;
    }

    it++;
  }

  while (true) {
    auto pdu = readPduBlocking();
    if ((pdu->getSequenceNumber() == nSequenceNumber &&
         (pdu->getCommandId() == nResponseCommandId ||
          pdu->getCommandId() == constants::CMD_ID_GENERIC_NACK)) ||
        (pdu->getSequenceNumber() == 0 && pdu->getCommandId() == constants::CMD_ID_GENERIC_NACK)) {
      return pdu;
    } else {
      m_pduResponseQueue.push_back(pdu);
    }
  }
}

Pdu::SPtr SmppClient::readPduResponse() {
  if (!m_pduResponseQueue.empty()) {
    auto pdu = m_pduResponseQueue.back();
    m_pduResponseQueue.pop_back();
    return pdu;
  }

  return readPduBlocking();
}

Pdu::SPtr SmppClient::readPduBlocking() {
  boost::system::error_code ec;
  uint32_t nCommandLength;

  boost::asio::read(*m_ptrTcpSocket, boost::asio::buffer(&nCommandLength, 4),
                    boost::asio::transfer_exactly(4), ec);

  // TODO validate?

  if (ec) {
    // TODO handle error
  }

  boost::asio::streambuf buffPdu;
  std::ostream os(&buffPdu);
  os.write((char*)&nCommandLength, 4);

  boost::asio::read(*m_ptrTcpSocket, buffPdu,
                    boost::asio::transfer_exactly(ntohl(nCommandLength) - 4), ec);

  if (ec) {
    // TODO handle error
  }

  std::istream is(&buffPdu);
  return Pdu::deserialize(is);
}

void SmppClient::checkSessionState(session_util::SessionState enDesiredSessionState) const {
  if (this->m_enSessionState != enDesiredSessionState) {
    std::string strError = "Client in wrong state. Desired:";
    strError += session_util::sessionStateToString(enDesiredSessionState);
    strError += "; actual: ";
    strError += session_util::sessionStateToString(m_enSessionState);
    throw smpp::InvalidSessionStateException(strError);
  }
}

void SmppClient::checkTcpConnection() const {
  if (!m_ptrTcpSocket->is_open()) {
    throw smpp::TransportException("Socket is closed");
  }
}

}  // namespace smpp