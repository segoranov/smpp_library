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
    case SessionState::BOUND:
      return "BOUND";
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
