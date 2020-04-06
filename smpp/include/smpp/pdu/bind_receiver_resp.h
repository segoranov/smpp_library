#ifndef BIND_RECEIVER_RESP_H
#define BIND_RECEIVER_RESP_H

#include "smpp/smpp_constants.h"

namespace smpp {

template <uint32_t CommandId>
class BindResp;

using BindReceiverResp = BindResp<constants::CMD_ID_BIND_RECEIVER_RESP>;

}  // namespace smpp

#endif
