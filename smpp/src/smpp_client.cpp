#include "smpp/smpp_client.h"

#include <sstream>

#include "smpp/smpp_exceptions.h"

namespace smpp {

void SmppClient::checkTcpConnection() const {
  if (!m_ptrTcpSocket->is_open()) {
    throw TransportException("Socket is closed");
  }
}

void SmppClient::checkSessionState(session_util::SessionState enDesiredSessionState) const {
  if (m_enSessionState.load() != enDesiredSessionState) {
    std::stringstream error;
    error << "Invalid session state. Desired: "
          << session_util::sessionStateToString(enDesiredSessionState)
          << ". Actual: " << session_util::sessionStateToString(m_enSessionState.load());
    throw InvalidSessionStateException(error.str());
  }
}

}  // namespace smpp