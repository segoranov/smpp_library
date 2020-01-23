#ifndef BIND_RECEIVER_H
#define BIND_RECEIVER_H

#include "smpp/pdu/bind.h"
#include "smpp/smpp_constants.h"

namespace smpp {

using BindReceiver = Bind<constants::CMD_ID_BIND_RECEIVER>;

}

#endif
