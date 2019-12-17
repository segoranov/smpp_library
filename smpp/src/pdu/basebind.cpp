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
}

void BaseBind::writeBody(Buffer& buffer) const {
  buffer.writeNullTerminatedString(m_strSystemId.c_str());
  buffer.writeNullTerminatedString(m_strPassword);
  buffer.writeNullTerminatedString(m_strSystemType);
  buffer.writeInt8(m_nInterfaceVersion);
  buffer_util::writeAddress(buffer, m_address);
}

}  // namespace smpp