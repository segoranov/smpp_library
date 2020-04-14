#include "smpp/pdu/builder/outbind_builder.h"

namespace smpp::builder {

OutbindBuilder& OutbindBuilder::withSequenceNumber(uint32_t nSequenceNumber) {
  m_optSequenceNumber = nSequenceNumber;
  return *this;
}

OutbindBuilder& OutbindBuilder::withSystemId(const std::string& strSystemId) {
  m_optSystemId = strSystemId;
  return *this;
}

OutbindBuilder& OutbindBuilder::withPassword(const std::string& strPassword) {
  m_optPassword = strPassword;
  return *this;
}

void OutbindBuilder::checkAllValuesArePresent() const {
  if (!m_optSequenceNumber.has_value()) {
    throw UndefinedValueException("OutbindBuilder: Undefined sequence number");
  }

  if (!m_optSystemId.has_value())
    throw UndefinedValueException("OutbindBuilder: Undefined system id");

  if (!m_optPassword.has_value())
    throw UndefinedValueException("OutbindBuilder: Undefined password");
}

}  // namespace smpp::builder