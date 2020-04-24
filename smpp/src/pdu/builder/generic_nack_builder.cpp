#include "smpp/pdu/builder/generic_nack_builder.h"

namespace smpp::builder {

GenericNackBuilder& GenericNackBuilder::withCommandStatus(uint32_t nCommandStatus) {
  m_optCommandStatus = nCommandStatus;
  return *this;
}

GenericNackBuilder& GenericNackBuilder::withSequenceNumber(uint32_t nSequenceNumber) {
  m_optSequenceNumber = nSequenceNumber;
  return *this;
}

void GenericNackBuilder::checkAllValuesArePresent() const {
  if (!m_optCommandStatus.has_value())
    throw UndefinedValueException("GenericNackBuilder: Undefined command status");

  if (!m_optSequenceNumber.has_value()) {
    throw UndefinedValueException("GenericNackBuilder: Undefined sequence number");
  }
}

}  // namespace smpp::builder