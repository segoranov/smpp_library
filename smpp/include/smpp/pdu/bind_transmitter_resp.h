#ifndef BIND_TRANSMITTER_RESP_H
#define BIND_TRANSMITTER_RESP_H

// #include "smpp/pdu/bind_resp.h"
#include "smpp/smpp_constants.h"

namespace smpp {

template <uint32_t CommandId>
class BindResp;

using BindTransmitterResp = BindResp<constants::CMD_ID_BIND_TRANSMITTER_RESP>;

}  // namespace smpp

#endif
