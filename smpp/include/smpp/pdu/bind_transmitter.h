#ifndef BIND_TRANSMITTER_H
#define BIND_TRANSMITTER_H

#include "smpp/pdu/bind.h"
#include "smpp/smpp_constants.h"

namespace smpp {

using BindTransmitter = Bind<constants::CMD_ID_BIND_TRANSMITTER>;

}

#endif
