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

Tlv::Tlv(uint16_t nTag, uint16_t nLength, const std::vector<uint8_t>& vValue)
    : m_nTag{nTag}, m_nLength{nLength}, m_vValue{vValue} {}

void Tlv::setTag(uint16_t nTag) { m_nTag = nTag; }

void Tlv::setLength(uint16_t nLength) { m_nLength = nLength; }

void Tlv::setValue(const std::vector<uint8_t>& vValue) { m_vValue = vValue; }

uint16_t Tlv::getTag() const { return m_nTag; }

uint16_t Tlv::getLength() const { return m_nLength; }

std::vector<uint8_t> Tlv::getValue() const { return m_vValue; }

int Tlv::size() const { return 4 + m_vValue.size(); }

}  // namespace smpp

bool operator==(const smpp::Tlv& lhs, const smpp::Tlv& rhs) {
  return lhs.getTag() == rhs.getTag() && lhs.getLength() == rhs.getLength() &&
         lhs.getValue() == rhs.getValue();
}

bool operator!=(const smpp::Tlv& lhs, const smpp::Tlv& rhs) { return !(lhs == rhs); }