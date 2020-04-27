#include "smpp/pdu/unbind_resp.h"

#include "smpp/pdu/builder/unbind_resp_builder.h"
#include "smpp/util/serialization_util.h"

namespace smpp {

UnbindResp::UnbindResp() : Pdu{constants::CMD_ID_UNBIND_RESP} {}

UnbindResp::UnbindResp(const builder::UnbindRespBuilder& params)
    : Pdu{constants::CMD_ID_UNBIND_RESP} {
  params.checkAllValuesArePresent();
  m_nCommandLength = smpp::constants::PDU_HEADER_LENGTH;
  m_nCommandStatus = params.m_optCommandStatus.value();
  m_nSequenceNumber = params.m_optSequenceNumber.value();
}

void UnbindResp::serialize(std::ostream& os) const { Pdu::serialize(os); }

std::unique_ptr<UnbindResp> UnbindResp::create(std::istream& is) {
  // std::cout << "UnbindResp::create()";
  return std::unique_ptr<UnbindResp>{new UnbindResp{}};
}

bool UnbindResp::equals(const Pdu& other) const { return Pdu::equals(other); }

}  // namespace smpp
