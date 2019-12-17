#ifndef TLV_H
#define TLV_H

#include <algorithm>
#include <iomanip>
#include <string>
#include <vector>

namespace smpp {

/**
 * TLV container class.
 */
class Tlv {
 private:
  uint16_t m_nTag = 0;
  uint16_t m_nLength = 0;
  std::vector<uint8_t> m_vValue;

 public:
  /**
   * Constructs a Tlv with only the tag.
   * @param nTag Tlv tag.
   */
  explicit Tlv(uint16_t nTag) : m_nTag{nTag} {}

  /**
   * Constructs a Tlv that stores a integer as an uint8_t.
   * @param nTag Tlv tag.
   * @param value Tlv value.
   */
  Tlv(const uint16_t& nTag, int nValue) : m_nTag{nTag}, m_nLength{1}, m_vValue{m_nLength} {
    m_vValue[0] = nValue & 0xff;
  }

  /**
   * Constructs a Tlv with a uint8_t value.
   * @param nTag Tlv tag.
   * @param nValue Tlv value.
   */
  Tlv(const uint16_t& nTag, uint8_t nValue) : m_nTag{nTag}, m_nLength{1}, m_vValue{m_nLength} {
    m_vValue[0] = nValue & 0xff;
  }

  /**
   * Constructs a Tlv with a uint16_t value.
   * @param nTag Tlv tag.
   * @param value Tlv value.
   */
  Tlv(const uint16_t& nTag, uint16_t value) : m_nTag{nTag}, m_nLength{2}, m_vValue{m_nLength} {
    m_vValue[0] = (value >> 8) & 0xff;
    m_vValue[1] = value & 0xff;
  }

  /**
   * Constructs a Tlv with a uint32_t value.
   * @param nTag Tlv tag.
   * @param value Tlv value.
   */
  Tlv(const uint16_t& nTag, uint32_t value) : m_nTag{nTag}, m_nLength{4}, m_vValue{m_nLength} {
    m_vValue[0] = (value >> 24) & 0xff;
    m_vValue[1] = (value >> 16) & 0xff;
    m_vValue[2] = (value >> 8) & 0xff;
    m_vValue[3] = value & 0xff;
  }

  /**
   * Constructs a Tlv with a string value.
   * @param nTag Tlv tag.
   * @param value Tlv value.
   */
  Tlv(const uint16_t& nTag, const std::string& s)
      : m_nTag{nTag}, m_nLength{s.length()}, m_vValue{m_nLength} {
    std::copy(s.begin(), s.end(), m_vValue.begin());
  }

  /**
   * Constructs a Tlv with an array of m_vValue.
   * @param nTag Tlv tag.
   * @param nLength Length of octet array.
   * @param _m_vValue Array of m_vValue.
   */
  Tlv(const uint16_t& nTag, const uint16_t& nLength, const std::vector<uint8_t>& vOctets)
      : m_nTag{nTag}, m_nLength{nLength}, m_vValue{vOctets} {}

  uint16_t getTag() const { return m_nTag; }

  uint16_t getLength() const { return m_nLength; }

  std::vector<uint8_t> getValue() const { return m_vValue; }
};

}  // namespace smpp

#endif