#ifndef BIND_TRANSCEIVER_H
#define BIND_TRANSCEIVER_H

#include "smpp/pdu/bind.h"
#include "smpp/smpp_constants.h"

namespace smpp {

using BindTransceiver = Bind<constants::CMD_ID_BIND_TRANSCEIVER>;

}

#endif
