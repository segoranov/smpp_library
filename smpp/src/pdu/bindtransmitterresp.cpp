#include "pdu/bindtransmitterresp.h"

#include "smppconstants.h"

namespace smpp {

BindTransmitterResp::BindTransmitterResp()
    : BaseBindResp{constants::CMD_ID_BIND_TRANSMITTER_RESP} {}

}  // namespace smpp