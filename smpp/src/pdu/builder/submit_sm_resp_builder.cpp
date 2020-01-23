#include "smpp/pdu/builder/submit_sm_resp_builder.h"

namespace smpp::builder {

SubmitSmRespBuilder& SubmitSmRespBuilder::withCommandStatus(uint32_t nCommandStatus) {
  m_optCommandStatus = nCommandStatus;
  return *this;
}

SubmitSmRespBuilder& SubmitSmRespBuilder::withSequenceNumber(uint32_t nSequenceNumber) {
  m_optSequenceNumber = nSequenceNumber;
  return *this;
}

SubmitSmRespBuilder& SubmitSmRespBuilder::withMessageId(const std::string& strMessageId) {
  m_optMessageId = strMessageId;
  return *this;
}

SubmitSmRespBuilder& SubmitSmRespBuilder::withOptionalParameters(const std::vector<Tlv>& tlvs) {
  m_vOptionalTlvParameters = tlvs;
  return *this;
}

void SubmitSmRespBuilder::checkAllValuesArePresent() const {
  if (!m_optCommandStatus.has_value()) {
    throw UndefinedValueException("SubmitSmRespBuilder: Undefined command status");
  }

  if (!m_optSequenceNumber.has_value()) {
    throw UndefinedValueException("SubmitSmRespBuilder: Undefined sequence number");
  }

  if (!m_optMessageId.has_value()) {
    throw UndefinedValueException("SubmitSmRespBuilder: Undefined message id");
  }
}

}  // namespace smpp::builder