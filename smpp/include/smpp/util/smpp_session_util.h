#ifndef SMPP_SESSION_UTIL_H
#define SMPP_SESSION_UTIL_H

#include <inttypes.h>

#include <sstream>

namespace smpp::session_util {

enum class SessionState {
  /** Session is in an initial state (not connected, but created) */
  INITIAL,

  /** Session is connected and a bind is pending */
  OPEN,

  /**
   * Session is in the process of binding.  If local is ESME, we sent the bind request.
   * If the local is SMSC, then the ESME initiated a bind request, but we have't responded yet.
   */
  BINDING,

  /** Session is bound as transceiver, receiver or transceiver (ready to process requests) */
  BOUND_TX,
  BOUND_RX,
  BOUND_TRX,

  /**
   * Session is in the process of unbinding. This may have been initiated by us or them.
   */
  UNBINDING,

  /** Session is unbound - unbind and unbind_resp PDUs have been exchanged */
  UNBOUND,

  /** Session is unbound and closed (destroyed) */
  CLOSED
};

std::string sessionStateToString(SessionState enSessionState);

}  // namespace smpp::session_util

#endif
