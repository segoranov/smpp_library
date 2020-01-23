#ifndef BIND_RECEIVER_RESP_H
#define BIND_RECEIVER_RESP_H

#include "smpp/pdu/bind_resp.h"
#include "smpp/smpp_constants.h"

namespace smpp {

using BindReceiverResp = BindResp<constants::CMD_ID_BIND_RECEIVER_RESP>;

}

#endif
