#include "pdu/base_bind.h"

namespace smpp {

BaseBind::BaseBind(uint32_t nCommandId) : PduRequest{nCommandId} {}

std::string BaseBind::getSystemId() const { return m_strSystemId; }

std::string BaseBind::getPassword() const { return m_strPassword; }

std::string BaseBind::getSystemType() const { return m_strSystemType; }

uint8_t BaseBind::getInterfaceVersion() const { return m_nInterfaceVersion; }

Address BaseBind::getAddress() const { return m_address; }

void BaseBind::setSystemId(const std::string& strSystemId) { m_strSystemId = strSystemId; }

void BaseBind::setSystemType(const std::string& strSystemType) { m_strSystemType = strSystemType; }

void BaseBind::setPassword(const std::string& strPassword) { m_strPassword = strPassword; }

void BaseBind::setInterfaceVersion(uint8_t nInterfaceVersion) {
  m_nInterfaceVersion = nInterfaceVersion;
}

void BaseBind::setAddress(const Address& newAddress) { m_address = newAddress; }

void BaseBind::serializeBody(std::ostream& os) const {
  binary::serializeNullTerminatedString(m_strSystemId, os);
  binary::serializeNullTerminatedString(m_strPassword, os);
  binary::serializeNullTerminatedString(m_strSystemType, os);
  binary::serializeInt8(m_nInterfaceVersion, os);
  m_address.serialize(os);
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

  Address address;
  address.deserialize(is);
  setAddress(address);
}

}  // namespace smpp