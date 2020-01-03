#include "pdu/base_bind.h"

namespace smpp {

BaseBind::BaseBind(uint32_t nCommandId) : PduRequest{nCommandId} {}

std::string BaseBind::getSystemId() const { return m_strSystemId; }

std::string BaseBind::getPassword() const { return m_strPassword; }

std::string BaseBind::getSystemType() const { return m_strSystemType; }

uint8_t BaseBind::getInterfaceVersion() const { return m_nInterfaceVersion; }

uint8_t BaseBind::getAddrTon() const { return m_nAddrTon; }

uint8_t BaseBind::getAddrNpi() const { return m_nAddrNpi; }

std::string BaseBind::getAddressRange() const { return m_strAddressRange; }

void BaseBind::setSystemId(const std::string& strSystemId) { m_strSystemId = strSystemId; }

void BaseBind::setSystemType(const std::string& strSystemType) { m_strSystemType = strSystemType; }

void BaseBind::setPassword(const std::string& strPassword) { m_strPassword = strPassword; }

void BaseBind::setInterfaceVersion(uint8_t nInterfaceVersion) {
  m_nInterfaceVersion = nInterfaceVersion;
}

void BaseBind::setAddrTon(uint8_t nAddrTon) { m_nAddrTon = nAddrTon; }

void BaseBind::setAddrNpi(uint8_t nAddrNpi) { m_nAddrNpi = nAddrNpi; }

void BaseBind::setAddressRange(const std::string& strAddressRange) {
  m_strAddressRange = strAddressRange;
}

void BaseBind::serializeBody(std::ostream& os) const {
  binary::serializeNullTerminatedString(m_strSystemId, os);
  binary::serializeNullTerminatedString(m_strPassword, os);
  binary::serializeNullTerminatedString(m_strSystemType, os);
  binary::serializeInt8(m_nInterfaceVersion, os);
  binary::serializeInt8(m_nAddrTon, os);
  binary::serializeInt8(m_nAddrNpi, os);
  binary::serializeNullTerminatedString(m_strAddressRange, os);
  serializeOptionalParameters(os);  // optional parameters are part of the body
}

void BaseBind::deserializeBody(std::istream& is) {
  const std::string strSystemId = binary::deserializeNullTerminatedString(is);
  setSystemId(strSystemId);

  const std::string strPassword = binary::deserializeNullTerminatedString(is);
  setPassword(strPassword);

  const std::string strSystemType = binary::deserializeNullTerminatedString(is);
  setSystemType(strSystemType);

  const uint8_t nInterfaceVersion = binary::deserializeInt8(is);
  setInterfaceVersion(nInterfaceVersion);

  const uint8_t nAddrTon = binary::deserializeInt8(is);
  setAddrTon(nAddrTon);

  const uint8_t nAddrNpi = binary::deserializeInt8(is);
  setAddrNpi(nAddrNpi);

  const std::string strAddressRange = binary::deserializeNullTerminatedString(is);
  setAddressRange(strAddressRange);
}

}  // namespace smpp