#include "smpp/pdu/builder/enquire_link_resp_builder.h"

namespace smpp::builder {

EnquireLinkRespBuilder& EnquireLinkRespBuilder::withSequenceNumber(uint32_t nSequenceNumber) {
  m_optSequenceNumber = nSequenceNumber;
  return *this;
}

void EnquireLinkRespBuilder::checkAllValuesArePresent() const {
  if (!m_optSequenceNumber.has_value()) {
    throw UndefinedValueException("EnquireLinkRespBuilder: Undefined sequence number");
  }
}

}  // namespace smpp::builder
