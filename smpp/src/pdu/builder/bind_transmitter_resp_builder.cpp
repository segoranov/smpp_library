#include "pdu/builder/bind_transmitter_resp_builder.h"

#include "smpp_constants.h"
#include "smpp_exceptions.h"

namespace smpp::builder {

BindTransmitterRespBuilder::BindTransmitterRespBuilder()
    : m_nCommandId{constants::CMD_ID_BIND_TRANSMITTER_RESP} {}

BindTransmitterRespBuilder BindTransmitterRespBuilder::BindTransmitterRespPdu() {
  return BindTransmitterRespBuilder();
}

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

std::unique_ptr<BindTransmitterResp> BindTransmitterRespBuilder::build() {
  if (!m_optCommandLength)
    throw UndefinedValueException("BindTransmitterRespBuilder: Undefined command length");

  if (!m_optCommandStatus)
    throw UndefinedValueException("BindTransmitterRespBuilder: Undefined command status");

  if (!m_optSequenceNumber)
    throw UndefinedValueException("BindTransmitterRespBuilder: Undefined sequence number");

  if (!m_optSystemId)
    throw UndefinedValueException("BindTransmitterRespBuilder: Undefined system id");

  return std::make_unique<BindTransmitterResp>(*this);
}

}  // namespace smpp::builder