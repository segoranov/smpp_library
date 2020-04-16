#ifndef SMPP_SESSION_H
#define SMPP_SESSION_H

#include <atomic>
#include <boost/asio.hpp>
#include <boost/asio/
#include <cstddef>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "smpp/pdu/pdu.h"

namespace smpp {

using boost::asio::ip::tcp;

/**
 * Defines a common interface for either a Client (ESME) or Server (SMSC) SMPP
 * session.
 */
class SmppSession {
 private:
  enum class Type;
  Type type;

  enum class State;
  std::atomic<unsigned> m_nSessionState;

  boost::asio::ip::tcp::socket m_tcpSocket;
  boost::asio::steady_timer m_sessionInitTimer{m_tcpSocket.get_executor()};

 public:
  /**
   * The type of SMPP session.  Will be either Server (SMSC) or Client (ESME).
   * Each side of the session has to be either one of these two.  It determines
   * which types of requests are possible to send to the other side.
   */
  enum class Type { SERVER, CLIENT };

  enum class State {
    /** Session is in an initial state (not connected, but created) */
    INITIAL,

    /** Session is connected and a bind is pending */
    OPEN,

    /**
     * Session is in the process of binding.  If local is ESME, we sent the bind request.
     * If the local is SMSC, then the ESME initiated a bind request, but we have't responded yet.
     */
    BINDING,

    /** Session is bound (ready to process requests) */
    BOUND,

    /**
     * Session is in the process of un-binding. This may have been initiated by us or them.
     */
    UNBINDING,

    /** Session is unbound - unbind and unbind_resp PDUs have been exchanged */
    UNBOUND,

    /** Session is unbound and closed (destroyed) */
    CLOSED
  };

  /**
   * Gets the session type of the local system.  If the local type is ESME,
   * then we are connected to an SMSC.  We are permitted to send submit_sm or
   * data_sm requests.
   *
   * @return The session type of the local system
   */
  virtual Type getLocalType() const = 0;

  /**
   * Gets the session type of the remote system.  If the remote type is SMSC,
   * then we are the ESME.  We are permitted to send submit_sm or data_sm
   * requests.
   *
   * @return The session type of the remote system
   */
  virtual Type getRemoteType() const = 0;

  /**
   * Checks if the session is currently in the "OPEN" state.  The "OPEN" state
   * means the session is connected and a bind is pending.
   * @return True if session is currently in the "OPEN" state, otherwise false.
   */
  virtual bool isOpen() const = 0;

  /**
   * Checks if the session is currently in the "BINDING" state.  The "BINDING"
   * state means the session is in the process of binding.  If local is ESME, we
   * sent the bind request, but have not yet received the bind response.  If the
   * local is SMSC, then the ESME initiated a bind request, but we have't
   * responded yet.
   * @return True if session is currently in the "BINDING" state, otherwise
   * false.
   */
  virtual bool isBinding() const = 0;

  /**
   * Checks if the session is currently in the "BOUND" state.  The "BOUND" state
   * means the session is bound and ready to process requests.
   * @return True if session is currently in the "BOUND" state, otherwise false.
   */
  virtual bool isBound() const = 0;

  /**
   * Checks if the session is currently in the "UNBINDING" state.  The
   * "UNBINDING" state means the session is in the process of unbinding. This
   * may have been initiated by us or them.
   * @return True if session is currently in the "UNBINDING" state, otherwise
   * false.
   */
  virtual bool isUnbinding() const = 0;

  /**
   * Checks if the session is currently in the "CLOSED" state.  The "CLOSED"
   * state means the session is unbound and closed (destroyed).
   * @return True if session is currently in the "CLOSED" state, otherwise
   * false.
   */
  virtual bool isClosed() const = 0;

  /**
   * Returns the time value of when this session reached
   * the "BOUND" state.
   * @return The time value when the session was bound.
   */
  virtual long getBoundTime() const = 0;

  enum class SmppBindType { TRANSCEIVER, TRANSMITTER, RECEIVER };

  /**
   * Gets the type of bind for this session such as "transceiver", "receiver",
   * or "transmitter".
   * @return The type of bind for this session
   */
  virtual SmppBindType getBindType() = 0;

  /**
   * Gets the name of the current state of the session.
   * @return The current state of the session by name such as "CLOSED"
   */
  virtual std::string getStateName() const = 0;

  /**
   * Gets the interface version currently in use between local and remote
   * endpoints.  This interface version is negotiated during the bind process
   * to mainly ensure that optional parameters are supported.
   * @return The interface version currently in use between local and remote
   * endpoints.
   */
  virtual std::byte getInterfaceVersion() const = 0;

  /**
   * Gets the underlying request "window" for this session.  A "window"
   * represents a request sent to the remote endpoint, but has not received a
   * response yet.  Accessing this property is useful if unacknowledged requests
   * need to be cleared out (most likely for a retry at a later time).
   * @return The request "window"
   */
  // virtual Window<Integer,PduRequest,PduResponse> getSendWindow() const = 0;

  /**
   * Gets the configuration associated with this session.
   * @return The session configuration
   */
  // virtual SmppSessionConfiguration getConfiguration() const = 0;

  /**
   * Immediately close the session by closing the underlying socket/channel.
   * This method will not attempt to "unbind" first, rather just immediately
   * close the channel.  Once closed, this session is not usable.  It is
   * always recommended an proper unbind is attempted first, rather than just
   * closing the socket.
   * @see #unbind(long)
   */
  virtual void close() = 0;

  /**
   * Attempts to "unbind" the session, waiting up to a specified period of
   * milliseconds for an unbind response from the remote endpoint.  Regardless
   * of whether a proper unbind response was received, the socket/channel is
   * closed.
   * @param timeoutMillis The number of milliseconds to wait until an unbind response is received
   * @see #close()
   */
  virtual void unbind(long timeoutMillis) = 0;
};

}  // namespace smpp

#endif