#include "pdu/bind_transmitter_resp.h"

#include "pdu/builder/bind_transmitter_resp_builder.h"
#include "smpp_constants.h"

namespace smpp {

BindTransmitterResp::BindTransmitterResp()
    : BaseBindResp{constants::CMD_ID_BIND_TRANSMITTER_RESP} {}

BindTransmitterResp::BindTransmitterResp(const builder::BindTransmitterRespBuilder& params)
    : BaseBindResp{constants::CMD_ID_BIND_TRANSMITTER_RESP} {
  if (!params.m_optCommandLength.has_value())
    throw UndefinedValueException("BindTransmitterResp(): Undefined command length");

  if (!params.m_optCommandStatus.has_value())
    throw UndefinedValueException("BindTransmitterResp(): Undefined command status");

  if (!params.m_optSequenceNumber.has_value())
    throw UndefinedValueException("BindTransmitterResp(): Undefined sequence number");

  if (!params.m_optSystemId.has_value())
    throw UndefinedValueException("BindTransmitterResp(): Undefined system id");

  // TODO SG: Throw exceptions here if invalid field exists
  m_nCommandLength = params.m_optCommandLength.value();
  m_nCommandStatus = params.m_optCommandStatus.value();
  m_nSequenceNumber = params.m_optSequenceNumber.value();
  m_strSystemId = params.m_optSystemId.value();
  m_vOptionalTlvParameters = params.m_vOptionalTlvParameters;
}

void BindTransmitterResp::serialize(std::ostream& os) const {
  serializeHeader(os);
  serializeBody(os);
}

std::unique_ptr<BindTransmitterResp> BindTransmitterResp::createPduBody(std::istream& is) {
  auto bindTransmitterRespPtr = std::unique_ptr<BindTransmitterResp>{new BindTransmitterResp{}};
  bindTransmitterRespPtr->deserializeBody(is);
  return bindTransmitterRespPtr;
}

}  // namespace smpp