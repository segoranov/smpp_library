#include "tlv/tlv.h"

#include <algorithm>
#include <iterator>

namespace smpp {

Tlv::Tlv(uint16_t nTag) : m_nTag{nTag} {}

Tlv::Tlv(uint16_t nTag, uint8_t nValue) : m_nTag{nTag}, m_nLength{1} {
  m_vValue.push_back(nValue & 0xff);
}

Tlv::Tlv(uint16_t nTag, uint16_t nValue) : m_nTag{nTag}, m_nLength{2} {
  m_vValue.push_back((nValue >> 8) & 0xff);
  m_vValue.push_back(nValue & 0xff);
}

Tlv::Tlv(uint16_t nTag, uint32_t nValue) : m_nTag{nTag}, m_nLength{4} {
  m_vValue.push_back((nValue >> 24) & 0xff);
  m_vValue.push_back((nValue >> 16) & 0xff);
  m_vValue.push_back((nValue >> 8) & 0xff);
  m_vValue.push_back(nValue & 0xff);
}

Tlv::Tlv(uint16_t nTag, const std::string& s)
    : m_nTag{nTag}, m_nLength{static_cast<uint16_t>(s.length())} {
  std::copy(s.begin(), s.end(), std::back_inserter(m_vValue));
}

Tlv::Tlv(uint16_t nTag, uint16_t nLength, const std::vector<uint8_t>& vOctets)
    : m_nTag{nTag}, m_nLength{nLength}, m_vValue{vOctets} {}

void Tlv::write(Buffer& buffer) const {
  buffer.writeInt16(m_nTag);
  buffer.writeInt16(m_nLength);
  std::for_each(m_vValue.begin(), m_vValue.end(),
                [&buffer](uint8_t octet) { buffer.writeInt8(octet); });
}

void Tlv::read(Buffer& buffer) {
  m_nTag = buffer.readInt16();
  m_nLength = buffer.readInt16();

  for (int i = 0; i < m_nLength; i++) {
    m_vValue.push_back(buffer.readInt8());
  }
}

}  // namespace smpp

bool operator==(const smpp::Tlv& lhs, const smpp::Tlv& rhs) {
  return lhs.getTag() == rhs.getTag() && lhs.getLength() == rhs.getLength() &&
         lhs.getValue() == rhs.getValue();
}