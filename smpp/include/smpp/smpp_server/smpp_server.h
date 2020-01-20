#ifndef SMPP_SERVER_H
#define SMPP_SERVER_H

#include "smpp/smpp_server/asio_generic_server.h"
#include "smpp/smpp_server/smpp_session_handler.h"

namespace smpp {

using SmppServer = AsioGenericServer<SmppSessionHandler>;

}

#endif