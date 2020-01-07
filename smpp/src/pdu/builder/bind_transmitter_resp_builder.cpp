#include "pdu/builder/bind_transmitter_resp_builder.h"

namespace smpp::builder {

BindTransmitterRespBuilder& BindTransmitterRespBuilder::withCommandLength(
    uint32_t nCommandLength) {
  m_optCommandLength = nCommandLength;
  return *this;
}

BindTransmitterRespBuilder& BindTransmitterRespBuilder::withCommandStatus(
    uint32_t nCommandStatus) {
  m_optCommandStatus = nCommandStatus;
  return *this;
}

BindTransmitterRespBuilder& BindTransmitterRespBuilder::withSequenceNumber(
    uint32_t nSequenceNumber) {
  m_optSequenceNumber = nSequenceNumber;
  return *this;
}

BindTransmitterRespBuilder& BindTransmitterRespBuilder::withSystemId(
    const std::string& strSystemId) {
  m_optSystemId = strSystemId;
  return *this;
}

BindTransmitterRespBuilder& BindTransmitterRespBuilder::withOptionalParameter(
    const smpp::Tlv& tlv) {
  m_vOptionalTlvParameters.push_back(tlv);
  return *this;
}

}  // namespace smpp::builder