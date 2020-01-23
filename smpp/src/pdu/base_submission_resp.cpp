#include "smpp/pdu/base_submission_resp.h"

#include "smpp/util/serialization_util.h"

namespace smpp {

BaseSubmissionResp::BaseSubmissionResp(uint32_t nCommandId) : Pdu{nCommandId} {}

std::string BaseSubmissionResp::getMessageId() const { return m_strMessageId; }

}  // namespace smpp