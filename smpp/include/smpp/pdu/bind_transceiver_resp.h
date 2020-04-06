#ifndef BIND_TRANSCEIVER_RESP_H
#define BIND_TRANSCEIVER_RESP_H

#include "smpp/smpp_constants.h"

namespace smpp {

template <uint32_t CommandId>
class BindResp;

using BindTransceiverResp = BindResp<constants::CMD_ID_BIND_TRANSCEIVER_RESP>;

}  // namespace smpp

#endif
