#include "smpp/pdu/builder/unbind_builder.h"

namespace smpp::builder {

UnbindBuilder& UnbindBuilder::withSequenceNumber(uint32_t nSequenceNumber) {
  m_optSequenceNumber = nSequenceNumber;
  return *this;
}

void UnbindBuilder::checkAllValuesArePresent() const {
  if (!m_optSequenceNumber.has_value()) {
    throw UndefinedValueException("UnbindBuilder: Undefined sequence number");
  }
}

}  // namespace smpp::builder
