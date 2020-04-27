#include "smpp/pdu/unbind.h"

#include "smpp/pdu/builder/unbind_builder.h"
#include "smpp/util/serialization_util.h"

namespace smpp {

Unbind::Unbind() : Pdu{constants::CMD_ID_UNBIND} {}

Unbind::Unbind(const builder::UnbindBuilder& params) : Pdu{constants::CMD_ID_UNBIND} {
  m_nCommandStatus = smpp::constants::command_status::ESME_ROK;
  params.checkAllValuesArePresent();
  m_nSequenceNumber = params.m_optSequenceNumber.value();
  m_nCommandLength = smpp::constants::PDU_HEADER_LENGTH;
}

void Unbind::serialize(std::ostream& os) const { Pdu::serialize(os); }

std::unique_ptr<Unbind> Unbind::create(std::istream& is) {
  // std::cout << "Unbind::create()";
  return std::unique_ptr<Unbind>{new Unbind{}};
}

bool Unbind::equals(const Pdu& other) const { return Pdu::equals(other); }

}  // namespace smpp
