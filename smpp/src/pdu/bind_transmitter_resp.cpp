#include "pdu/bind_transmitter_resp.h"

#include "pdu/builder/bind_transmitter_resp_builder.h"
#include "smpp_constants.h"

namespace smpp {

BindTransmitterResp::BindTransmitterResp()
    : BaseBindResp{constants::CMD_ID_BIND_TRANSMITTER_RESP} {}

void BindTransmitterResp::serialize(std::ostream& os) const {
  serializeHeader(os);
  serializeBody(os);
}

BindTransmitterResp::BindTransmitterResp(const builder::BindTransmitterRespBuilder& params)
    : BaseBindResp{constants::CMD_ID_BIND_TRANSMITTER_RESP} {
  // TODO SG: Throw exceptions here if invalid field exists
  m_nCommandLength = params.m_optCommandLength.value();
  m_nCommandStatus = params.m_optCommandStatus.value();
  m_nSequenceNumber = params.m_optSequenceNumber.value();
  m_strSystemId = params.m_optSystemId.value();
  m_vOptionalTlvParameters = params.m_vOptionalTlvParameters;
}

std::unique_ptr<BindTransmitterResp> BindTransmitterResp::createPduBody(std::istream& is) {
  auto bindTransmitterRespPtr = std::unique_ptr<BindTransmitterResp>{new BindTransmitterResp{}};
  bindTransmitterRespPtr->deserializeBody(is);
  return bindTransmitterRespPtr;
}

}  // namespace smpp