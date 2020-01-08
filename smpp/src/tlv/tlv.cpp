#include "smpp/tlv/tlv.h"

#include <algorithm>
#include <iterator>

#include "smpp/util/serialization_util.h"

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

Tlv::Tlv(uint16_t nTag, uint16_t nLength, const std::vector<uint8_t>& vValue)
    : m_nTag{nTag}, m_nLength{nLength}, m_vValue{vValue} {}

void Tlv::setTag(uint16_t nTag) { m_nTag = nTag; }

void Tlv::setLength(uint16_t nLength) { m_nLength = nLength; }

void Tlv::setValue(const std::vector<uint8_t>& vValue) { m_vValue = vValue; }

uint16_t Tlv::getTag() const { return m_nTag; }

uint16_t Tlv::getLength() const { return m_nLength; }

std::vector<uint8_t> Tlv::getValue() const { return m_vValue; }

int Tlv::size() const { return 4 + m_vValue.size(); }

void Tlv::serialize(std::ostream& os) const {
  binary::serializeInt16(m_nTag, os);
  binary::serializeInt16(m_nLength, os);

  for (uint8_t octet : m_vValue) {
    binary::serializeInt8(octet, os);
  }
}

void Tlv::deserialize(std::istream& is) {
  m_nTag = binary::deserializeInt16(is);
  m_nLength = binary::deserializeInt16(is);

  std::vector<uint8_t> tlvValue;
  for (int i = 0; i < m_nLength; i++) {
    tlvValue.push_back(binary::deserializeInt8(is));
  }

  m_vValue = tlvValue;
}

}  // namespace smpp

bool operator==(const smpp::Tlv& lhs, const smpp::Tlv& rhs) {
  return lhs.getTag() == rhs.getTag() && lhs.getLength() == rhs.getLength() &&
         lhs.getValue() == rhs.getValue();
}

bool operator!=(const smpp::Tlv& lhs, const smpp::Tlv& rhs) { return !(lhs == rhs); }