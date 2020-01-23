#ifndef SMPP_CLIENT_H
#define SMPP_CLIENT_H

#include <atomic>
#include <boost/asio.hpp>
#include <boost/shared_array.hpp>
#include <list>
#include <memory>

#include "commands.h"
#include "smpp/util/smpp_session_util.h"

namespace smpp {

class SmppClient {
 private:
  std::atomic<session_util::SessionState> m_enSessionState;

  using TcpSocket = boost::asio::ip::tcp::socket;
  std::shared_ptr<TcpSocket> m_ptrTcpSocket;

  using PduResponsePtr = std::shared_ptr<Pdu>;
  std::list<Pdu::Ptr> m_pduResponseQueue;

 public:
  SmppClient(std::shared_ptr<TcpSocket> tcpSocket) {}

  void bindTransmitter(const BindTransmitter& pdu);
  void bindTransceiver(const BindTransceiver& pdu);
  void bindReceiver(const BindReceiver& pdu);

 private:
  /**
   * @brief Sends bind PDU to the server
   *
   * @throw TransportException if something is wrong with the TCP connection
   * @throw InvalidSessionStateException if the session is not in OPEN state
   */
  template <uint32_t CommandId>
  void bind(const Bind<CommandId>& pdu);

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
   * Sends a request PDU through the socket
   */
  void sendPdu(Pdu::Ptr pdu);

  void readPduBlocking();

  void readPduBlocking(boost::shared_array<uint8_t> commandLengthBuffer);


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
  Pdu::Ptr readPduResponse(uint32_t nSequenceNumber, uint32_t nCommandId);

  Pdu::Ptr readPdu(bool bSynchronous);
};

template <uint32_t CommandId>
void SmppClient::bind(const Bind<CommandId>& pdu) {
  // check if TCP connection is okay
  // if it is not OKAY, throw TransportException
  checkTcpConnection();

  // check if session state is OPEN
  // if it is not OPEN, throw InvalidSessionStateException
  checkSessionState(session_util::SessionState::OPEN);

  // send the pdu through the socket
  // receive the pdu response
  sendPdu(pdu);
  auto pduResponse = readPduResponse(pdu->getSequenceNumber(), pdu->getCommandId());

  // check if the response is OK
  // if it is not ok, check the command status and throw proper exception
  // for example InvalidPassswordException or InvalidSystemIdException

  // if the response is OK, set the session state to BOUND
}

}  // namespace smpp

#endif