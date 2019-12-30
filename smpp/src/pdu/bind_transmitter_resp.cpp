#include "pdu/bind_transmitter_resp.h"

#include "smpp_constants.h"

namespace smpp {

BindTransmitterResp::BindTransmitterResp()
    : BaseBindResp{constants::CMD_ID_BIND_TRANSMITTER_RESP} {}

void BindTransmitterResp::serialize(std::ostream& os) const {
  serializeHeader(os);
  serializeBody(os);
}

}  // namespace smpp