#ifndef BIND_TRANSMITTER_RESP_H
#define BIND_TRANSMITTER_RESP_H

#include "smpp/pdu/bind_resp.h"
#include "smpp/smpp_constants.h"

namespace smpp {

using BindTransmitterResp = BindResp<constants::CMD_ID_BIND_TRANSMITTER_RESP>;

}

#endif
