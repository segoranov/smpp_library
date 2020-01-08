#include "smpp/pdu/builder/bind_builder.h"

namespace smpp::builder {

BindBuilder& BindBuilder::withCommandLength(uint32_t nCommandLength) {
  m_optCommandLength = nCommandLength;
  return *this;
}

BindBuilder& BindBuilder::withCommandStatus(uint32_t nCommandStatus) {
  m_optCommandStatus = nCommandStatus;
  return *this;
}

BindBuilder& BindBuilder::withSequenceNumber(uint32_t nSequenceNumber) {
  m_optSequenceNumber = nSequenceNumber;
  return *this;
}

BindBuilder& BindBuilder::withSystemId(const std::string& strSystemId) {
  m_optSystemId = strSystemId;
  return *this;
}

BindBuilder& BindBuilder::withPassword(const std::string& strPassword) {
  m_optPassword = strPassword;
  return *this;
}

BindBuilder& BindBuilder::withSystemType(const std::string& strSystemType) {
  m_optSystemType = strSystemType;
  return *this;
}

BindBuilder& BindBuilder::withInterfaceVersion(uint8_t nInterfaceVersion) {
  m_optInterfaceVersion = nInterfaceVersion;
  return *this;
}

BindBuilder& BindBuilder::withAddrTon(uint8_t nAddrTon) {
  m_optAddrTon = nAddrTon;
  return *this;
}

BindBuilder& BindBuilder::withAddrNpi(uint8_t nAddrNpi) {
  m_optAddrNpi = nAddrNpi;
  return *this;
}

BindBuilder& BindBuilder::withAddressRange(
    const std::string& strAddressRange) {
  m_optAddressRange = strAddressRange;
  return *this;
}

}  // namespace smpp::builder