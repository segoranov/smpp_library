#include "smpp/pdu/builder/outbind_builder.h"

namespace smpp::builder {

OutbindBuilder& OutbindBuilder::withCommandStatus(uint32_t nCommandStatus) {
  m_optCommandStatus = nCommandStatus;
  return *this;
}

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

}  // namespace smpp::builder