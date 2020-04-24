#include "smpp/pdu/generic_nack.h"

#include "smpp/pdu/builder/generic_nack_builder.h"
#include "smpp/util/serialization_util.h"

namespace smpp {

GenericNack::GenericNack() : Pdu{constants::CMD_ID_GENERIC_NACK} {}

GenericNack::GenericNack(const builder::GenericNackBuilder& params)
    : Pdu{constants::CMD_ID_GENERIC_NACK} {
  params.checkAllValuesArePresent();
  m_nCommandLength = smpp::constants::PDU_HEADER_LENGTH;
  m_nCommandStatus = params.m_optCommandStatus.value();
  m_nSequenceNumber = params.m_optSequenceNumber.value();
}

void GenericNack::serialize(std::ostream& os) const { Pdu::serialize(os); }

std::unique_ptr<GenericNack> GenericNack::create(std::istream& is) {
  // std::cout << "GenericNack::create()";
  return std::unique_ptr<GenericNack>{new GenericNack{}};
}

bool GenericNack::equals(const Pdu& other) const { return Pdu::equals(other); }

}  // namespace smpp
