#ifndef SMPP_SERVER_H
#define SMPP_SERVER_H

#include <string>

#include "smpp/smpp_server/asio_generic_server.h"
#include "smpp/smpp_server/smpp_session_handler.h"

namespace smpp {

class SmppServer : public AsioGenericServer<SmppSessionHandler> {
 private:
 public:
  void outbind(const std::string& strRemoteIp, const std::string& strRemotePort);
};

}  // namespace smpp

#endif