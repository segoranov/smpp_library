#ifndef SMPP_CLIENT_H
#define SMPP_CLIENT_H

#include "commands.h"

namespace smpp {

class SmppClient {
 private:
 public:
 private:

  /**
   * @brief Sends bind PDU to the server
   * 
   * @throw TransportException, if the TCP connection is not okay
   * @throw 
   * 
   */
  template <uint32_t CommandId>
  void bind(const Bind<CommandId>& pdu) {
      // check if TCP connection is okay
      // if it is not OKAY, throw TransportException

      // check if session state is OPEN
      // if it is not OPEN, throw InvalidSessionStateException

      // send the pdu through the socket
      // receive the pdu response

      // check if the response is OK
      // if it is not ok, check the command status and throw proper exception
      // for example InvalidPassswordException or InvalidSystemIdException

      // if the response is OK, set the session state to BOUND
  }
};

}  // namespace smpp

#endif