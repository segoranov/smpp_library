#ifndef BIND_TRANSCEIVER_RESP_H
#define BIND_TRANSCEIVER_RESP_H

#include "smpp/pdu/bind_resp.h"
#include "smpp/smpp_constants.h"

namespace smpp {

using BindTransceiverResp = BindResp<constants::CMD_ID_BIND_TRANSCEIVER_RESP>;

}

#endif
