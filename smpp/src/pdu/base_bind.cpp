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
  m_strSystemId = strSystemId;

  const std::string strPassword = binary::deserializeNullTerminatedString(is);
  m_strPassword = strPassword;

  const std::string strSystemType = binary::deserializeNullTerminatedString(is);
  m_strSystemType = strSystemType;

  const uint8_t nInterfaceVersion = binary::deserializeInt8(is);
  m_nInterfaceVersion = nInterfaceVersion;

  const uint8_t nAddrTon = binary::deserializeInt8(is);
  m_nAddrTon = nAddrTon;

  const uint8_t nAddrNpi = binary::deserializeInt8(is);
  m_nAddrNpi = nAddrNpi;

  const std::string strAddressRange = binary::deserializeNullTerminatedString(is);
  m_strAddressRange = strAddressRange;
}

}  // namespace smpp