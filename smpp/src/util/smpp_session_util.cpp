#include "smpp/util/smpp_session_util.h"

namespace smpp::session_util {

std::string sessionStateToString(SessionState enSessionState) {
  switch (enSessionState) {
    case SessionState::INITIAL:
      return "INITIAL";
    case SessionState::OPEN:
      return "OPEN";
    case SessionState::BINDING:
      return "BINDING";
    case SessionState::BOUND_RX:
      return "BOUND_RX";
    case SessionState::BOUND_TRX:
      return "BOUND_TRX";
    case SessionState::BOUND_TX:
      return "BOUND_TX";
    case SessionState::UNBINDING:
      return "UNBINDING";
    case SessionState::UNBOUND:
      return "UNBOUND";
    case SessionState::CLOSED:
      return "CLOSED";
    default:
      return "UNKNOWN_SESSION_STATE";
  }
}

}  // namespace smpp::session_util
