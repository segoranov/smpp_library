#include "pdu/basebind.h"

#include "util/buffer_util.h"

namespace smpp {

BaseBind::BaseBind(uint32_t nCommandId) : PduRequest{nCommandId} {}

void BaseBind::readBody(Buffer& buffer) {
  m_strSystemId = buffer.readNullTerminatedString();
  m_strPassword = buffer.readNullTerminatedString();
  m_strSystemType = buffer.readNullTerminatedString();
  m_nInterfaceVersion = buffer.readInt8();
  m_address = buffer_util::readAddress(buffer);
  readOptionalParameters(buffer);
}

void BaseBind::writeBody(Buffer& buffer) const {
  buffer.writeNullTerminatedString(m_strSystemId.c_str());
  buffer.writeNullTerminatedString(m_strPassword);
  buffer.writeNullTerminatedString(m_strSystemType);
  buffer.writeInt8(m_nInterfaceVersion);
  buffer_util::writeAddress(buffer, m_address);
  writeOptionalParameters(buffer);
}

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