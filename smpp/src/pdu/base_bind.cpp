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

}  // namespace smpp