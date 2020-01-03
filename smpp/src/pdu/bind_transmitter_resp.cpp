#include "pdu/bind_transmitter_resp.h"

#include "smpp_constants.h"

namespace smpp {

BindTransmitterResp::BindTransmitterResp()
    : BaseBindResp{constants::CMD_ID_BIND_TRANSMITTER_RESP} {}

void BindTransmitterResp::serialize(std::ostream& os) const {
  serializeHeader(os);
  serializeBody(os);
}

std::unique_ptr<BindTransmitterResp> BindTransmitterResp::createEmpty() {
  return std::unique_ptr<BindTransmitterResp>{new BindTransmitterResp{}};
}

std::unique_ptr<BindTransmitterResp> BindTransmitterResp::createPduBody(std::istream& is) {
  auto bindTransmitterRespPtr = std::unique_ptr<BindTransmitterResp>{new BindTransmitterResp{}};
  bindTransmitterRespPtr->deserializeBody(is);
  return bindTransmitterRespPtr;
}

}  // namespace smpp