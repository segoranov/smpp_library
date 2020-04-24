#include "smpp/pdu/builder/enquire_link_builder.h"

namespace smpp::builder {

EnquireLinkBuilder& EnquireLinkBuilder::withSequenceNumber(uint32_t nSequenceNumber) {
  m_optSequenceNumber = nSequenceNumber;
  return *this;
}

void EnquireLinkBuilder::checkAllValuesArePresent() const {
  if (!m_optSequenceNumber.has_value()) {
    throw UndefinedValueException("EnquireLinkBuilder: Undefined sequence number");
  }
}

}  // namespace smpp::builder
