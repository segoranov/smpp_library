#include "smpp/pdu/submit_sm_resp.h"

#include "smpp/pdu/builder/submit_sm_resp_builder.h"
#include "smpp/smpp_constants.h"
#include "smpp/util/serialization_util.h"

namespace smpp {

SubmitSmResp::SubmitSmResp() : BaseSubmissionResp{constants::CMD_ID_SUBMIT_SM_RESP} {}

SubmitSmResp::SubmitSmResp(const builder::SubmitSmRespBuilder& params)
    : BaseSubmissionResp{constants::CMD_ID_SUBMIT_SM_RESP} {
  if (!params.m_optCommandStatus.has_value()) {
    throw UndefinedValueException("SubmitSmResp(): Undefined command status");
  }

  if (!params.m_optSequenceNumber.has_value()) {
    throw UndefinedValueException("SubmitSmResp(): Undefined sequence number");
  }

  if (!params.m_optMessageId.has_value()) {
    throw UndefinedValueException("SubmitSmResp(): Undefined message id");
  }

  m_nCommandStatus = params.m_optCommandStatus.value();
  m_nSequenceNumber = params.m_optSequenceNumber.value();

  m_strMessageId = params.m_optMessageId.value();
  m_vOptionalTlvParameters = params.m_vOptionalTlvParameters;

  // Add PDU header to command length
  m_nCommandLength = smpp::constants::PDU_HEADER_LENGTH;

  // Add C-octet strings to command length without forgetting to add 1
  // for the null terminating character
  m_nCommandLength += m_strMessageId.size() + 1;

  // Add optional parameters size to command length
  for (const auto& tlv : m_vOptionalTlvParameters) {
    m_nCommandLength += tlv.size();
  }
}

std::unique_ptr<SubmitSmResp> SubmitSmResp::create(std::istream& is) {
  auto submitSmRespPtr = std::unique_ptr<SubmitSmResp>{new SubmitSmResp{}};

  const std::string strMessageId = binary::deserializeNullTerminatedString(is);
  submitSmRespPtr->m_strMessageId = strMessageId;

  submitSmRespPtr->deserializeOptionalParameters(is);

  return submitSmRespPtr;
}

void SubmitSmResp::serialize(std::ostream& os) const {
  serializeHeader(os);
  binary::serializeNullTerminatedString(m_strMessageId, os);
  serializeOptionalParameters(os);
}

}  // namespace smpp