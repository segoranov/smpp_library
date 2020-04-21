#ifndef SMPP_CLIENT_H
#define SMPP_CLIENT_H

#include <atomic>
#include <boost/asio.hpp>
#include <boost/shared_array.hpp>
#include <iostream>
#include <list>
#include <memory>

#include "commands.h"
#include "smpp/util/smpp_session_util.h"

namespace smpp {

class SmppClient {
 public:
  using TcpSocket = boost::asio::ip::tcp::socket;
  explicit SmppClient(std::shared_ptr<TcpSocket> ptrTcpSocket);

  /**
   * @brief Sends bind PDU to the server
   *
   * The function blocks until the corresponding bind_resp is returned
   *
   * @throw TransportException if something is wrong with the TCP connection
   * @throw InvalidSessionStateException if the session is not in OPEN state
   *
   * @return bind response
   */
  template <uint32_t CommandId>
  Pdu::SPtr bind(const Bind<CommandId>& pdu);

  /**
   * @brief Sends unbind PDU to the server and blocks until unbind_resp is received
   */
  Pdu::SPtr unbind();

  /**
   * @brief Sends PDU to the server and blocks until corresponding reponse is received
   *
   *
   */
  Pdu::SPtr sendPduSync(Pdu::SPtr pdu);

  /**
   * @brief Initiates asynchronous sending of a PDU to the server and returns immediately
   */
  void sendPduAsync(Pdu::SPtr pdu);

  /**
   * Returns a response for a PDU we have sent,
   * specified by its sequence number and its command id.
   * First the PDU queue is checked for any responses,
   * if we don't find any we do a blocking read on the socket until
   * we get the desired response.
   *
   * @param nSequenceNumber Sequence number to look for.
   * @param nCommandId Command id to look for.
   * @return PDU response to PDU with the given sequence number and command id.
   */
  Pdu::SPtr readPduResponse(uint32_t nSequenceNumber, uint32_t nCommandId);

 private:
  /**
   * @brief Checks whether the TCP socket is open
   *
   * @throw TransportException if the socket is not open
   */
  void checkTcpConnection() const;

  /**
   * @brief Checks whether the session is in desired state
   *
   * @throw InvalidSessionStateException if the session is not the desired one
   */
  void checkSessionState(session_util::SessionState enDesiredSessionState) const;

  /**
   * @brief Checks whether the session is in appropriate state for transmitting a Pdu different
   * than bind
   *
   * @throw InvalidSessionStateException
   */
  void checkTransmissionIsPossible() const;

  /**
   * Sends a request PDU through the socket
   */
  void sendPdu(Pdu::SPtr pdu);

  Pdu::SPtr readPduBlocking();

 private:
  session_util::SessionState m_enSessionState;
  std::shared_ptr<TcpSocket> m_ptrTcpSocket;

  using PduResponsePtr = std::shared_ptr<Pdu>;
  std::list<Pdu::SPtr> m_pduResponseQueue;
};

template <uint32_t CommandId>
Pdu::SPtr SmppClient::bind(const Bind<CommandId>& pdu) {
  checkTcpConnection();
  checkSessionState(session_util::SessionState::OPEN);

  sendPdu(std::make_unique<Bind<CommandId>>(pdu));
  auto pduResponse = readPduResponse(pdu.getSequenceNumber(), pdu.getCommandId());

  if (pdu.getCommandStatus() == constants::errors::ESME_ROK) {
    switch (CommandId) {
      case constants::CMD_ID_BIND_RECEIVER: {
        m_enSessionState = session_util::SessionState::BOUND_RX;
      }
      case constants::CMD_ID_BIND_TRANSMITTER: {
        m_enSessionState = session_util::SessionState::BOUND_TX;
      }
      case constants::CMD_ID_BIND_TRANSCEIVER: {
        m_enSessionState = session_util::SessionState::BOUND_TRX;
      }
    }
  }

  return pduResponse;
}

}  // namespace smpp

#endif