#include "smpp/pdu/base_submission_resp.h"

#include "smpp/util/serialization_util.h"

namespace smpp {

BaseSubmissionResp::BaseSubmissionResp(uint32_t nCommandId) : Pdu{nCommandId} {}

void BaseSubmissionResp::serializeBody(std::ostream& os) const {
  binary::serializeNullTerminatedString(m_strMessageId, os);
}

void BaseSubmissionResp::deserializeBody(std::istream& is) {
  const std::string strMessageId = binary::deserializeNullTerminatedString(is);
  m_strMessageId = strMessageId;
}

std::string BaseSubmissionResp::getMessageId() const { return m_strMessageId; }

}  // namespace smpp