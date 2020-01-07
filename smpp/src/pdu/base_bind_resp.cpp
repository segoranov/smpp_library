#include "pdu/base_bind_resp.h"

#include "smpp_constants.h"
#include "util/serialization_util.h"

namespace smpp {

BaseBindResp::BaseBindResp(uint32_t nCommandId) : PduResponse{nCommandId} {}

std::string BaseBindResp::getSystemId() const { return m_strSystemId; }

void BaseBindResp::serializeBody(std::ostream& os) const {
  binary::serializeNullTerminatedString(m_strSystemId, os);
  serializeOptionalParameters(os);
}

void BaseBindResp::deserializeBody(std::istream& is) {
  const std::string strSystemId = binary::deserializeNullTerminatedString(is);
  m_strSystemId = strSystemId;

  deserializeOptionalParameters(is);
  if (m_vOptionalTlvParameters.size() > 1) {
    throw InvalidTagException{};
  }
}

}  // namespace smpp