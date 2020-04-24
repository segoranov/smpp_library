#include "smpp/pdu/enquire_link.h"

#include "smpp/pdu/builder/enquire_link_builder.h"
#include "smpp/util/serialization_util.h"

namespace smpp {

EnquireLink::EnquireLink() : Pdu{constants::CMD_ID_ENQUIRE_LINK} {}

EnquireLink::EnquireLink(const builder::EnquireLinkBuilder& params)
    : Pdu{constants::CMD_ID_ENQUIRE_LINK} {
  m_nCommandStatus = smpp::constants::errors::ESME_ROK;
  params.checkAllValuesArePresent();
  m_nSequenceNumber = params.m_optSequenceNumber.value();
  m_nCommandLength = smpp::constants::PDU_HEADER_LENGTH;
}

void EnquireLink::serialize(std::ostream& os) const { Pdu::serialize(os); }

std::unique_ptr<EnquireLink> EnquireLink::create(std::istream& is) {
  // std::cout << "EnquireLink::create()";
  return std::unique_ptr<EnquireLink>{new EnquireLink{}};
}

bool EnquireLink::equals(const Pdu& other) const { return Pdu::equals(other); }

}  // namespace smpp
