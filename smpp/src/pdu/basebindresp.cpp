#include "pdu/basebindresp.h"

namespace smpp {

BaseBindResp::BaseBindResp(uint32_t nCommandId) : PduResponse{nCommandId} {}

std::string BaseBindResp::getSystemId() const { return m_strSystemId; }

void BaseBindResp::setSystemId(const std::string& strSystemId) { m_strSystemId = strSystemId; }

}  // namespace smpp