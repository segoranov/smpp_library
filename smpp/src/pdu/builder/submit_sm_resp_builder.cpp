#include "smpp/pdu/builder/submit_sm_resp_builder.h"

namespace smpp::builder {

SubmitSmRespBuilder& SubmitSmRespBuilder::withCommandLength(uint32_t nCommandLength) {
  m_optCommandLength = nCommandLength;
  return *this;
}

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

}  // namespace smpp::builder