#include "pdu/builder/bind_transmitter_builder.h"

namespace smpp::builder {

BindTransmitterBuilder& BindTransmitterBuilder::withCommandLength(uint32_t nCommandLength) {
  m_optCommandLength = nCommandLength;
  return *this;
}

BindTransmitterBuilder& BindTransmitterBuilder::withCommandStatus(uint32_t nCommandStatus) {
  m_optCommandStatus = nCommandStatus;
  return *this;
}

BindTransmitterBuilder& BindTransmitterBuilder::withSequenceNumber(uint32_t nSequenceNumber) {
  m_optSequenceNumber = nSequenceNumber;
  return *this;
}

BindTransmitterBuilder& BindTransmitterBuilder::withSystemId(const std::string& strSystemId) {
  m_optSystemId = strSystemId;
  return *this;
}

BindTransmitterBuilder& BindTransmitterBuilder::withPassword(const std::string& strPassword) {
  m_optPassword = strPassword;
  return *this;
}

BindTransmitterBuilder& BindTransmitterBuilder::withSystemType(const std::string& strSystemType) {
  m_optSystemType = strSystemType;
  return *this;
}

BindTransmitterBuilder& BindTransmitterBuilder::withInterfaceVersion(uint8_t nInterfaceVersion) {
  m_optInterfaceVersion = nInterfaceVersion;
  return *this;
}

BindTransmitterBuilder& BindTransmitterBuilder::withAddrTon(uint8_t nAddrTon) {
  m_optAddrTon = nAddrTon;
  return *this;
}

BindTransmitterBuilder& BindTransmitterBuilder::withAddrNpi(uint8_t nAddrNpi) {
  m_optAddrNpi = nAddrNpi;
  return *this;
}

BindTransmitterBuilder& BindTransmitterBuilder::withAddressRange(
    const std::string& strAddressRange) {
  m_optAddressRange = strAddressRange;
  return *this;
}

}  // namespace smpp::builder