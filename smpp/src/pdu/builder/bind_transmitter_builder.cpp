#include "pdu/builder/bind_transmitter_builder.h"

#include "smpp_constants.h"
#include "smpp_exceptions.h"

namespace smpp::builder {

BindTransmitterBuilder::BindTransmitterBuilder()
    : m_nCommandId{constants::CMD_ID_BIND_TRANSMITTER} {}

BindTransmitterBuilder BindTransmitterBuilder::BindTransmitterPdu() {
  return BindTransmitterBuilder();
}

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

std::unique_ptr<BindTransmitter> BindTransmitterBuilder::build() {
  if (!m_optCommandLength)
    throw UndefinedValueException("BindTransmitterBuilder: Undefined command length");

  if (!m_optCommandStatus)
    throw UndefinedValueException("BindTransmitterBuilder: Undefined command status");

  if (!m_optSequenceNumber)
    throw UndefinedValueException("BindTransmitterBuilder: Undefined sequence number");

  if (!m_optSystemId) throw UndefinedValueException("BindTransmitterBuilder: Undefined system id");

  if (!m_optSystemType)
    throw UndefinedValueException("BindTransmitterBuilder: Undefined system type");

  if (!m_optInterfaceVersion)
    throw UndefinedValueException("BindTransmitterBuilder: Undefined interface version");

  if (!m_optAddrTon) throw UndefinedValueException("BindTransmitterBuilder: Undefined addr ton");

  if (!m_optAddrNpi) throw UndefinedValueException("BindTransmitterBuilder: Undefined addr npi");

  if (!m_optAddressRange)
    throw UndefinedValueException("BindTransmitterBuilder: Undefined address range");

  return std::make_unique<BindTransmitter>(*this);
}

}  // namespace smpp::builder