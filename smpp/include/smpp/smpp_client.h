#ifndef SMPP_CLIENT_H
#define SMPP_CLIENT_H

#include <atomic>
#include <boost/asio.hpp>
#include <memory>

#include "commands.h"
#include "smpp/util/smpp_session_util.h"

namespace smpp {

class SmppClient {
 private:
  std::atomic<session_util::SessionState> m_enSessionState;

  using TcpSocket = boost::asio::ip::tcp::socket;
  std::shared_ptr<TcpSocket> m_ptrTcpSocket;

 public:
  SmppClient(std::shared_ptr<TcpSocket> tcpSocket) {}

 private:
  /**
   * @brief Sends bind PDU to the server
   *
   * @throw TransportException if something is wrong with the TCP connection
   * @throw
   *
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

  // check if the response is OK
  // if it is not ok, check the command status and throw proper exception
  // for example InvalidPassswordException or InvalidSystemIdException

  // if the response is OK, set the session state to BOUND
}

}  // namespace smpp

#endif