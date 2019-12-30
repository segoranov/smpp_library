#include "pdu/base_bind_resp.h"

#include "util/serialization_util.h"

namespace smpp {

BaseBindResp::BaseBindResp(uint32_t nCommandId) : PduResponse{nCommandId} {}

std::string BaseBindResp::getSystemId() const { return m_strSystemId; }

void BaseBindResp::setSystemId(const std::string& strSystemId) { m_strSystemId = strSystemId; }

void BaseBindResp::serializeBody(std::ostream& os) const {
  binary::serializeNullTerminatedString(m_strSystemId, os);
  serializeOptionalParameters(os);
}

}  // namespace smpp