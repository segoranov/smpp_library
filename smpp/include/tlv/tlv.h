#ifndef TLV_H
#define TLV_H

#include <algorithm>
#include <iomanip>
#include <string>
#include <vector>

#include "buffer/buffer.h"

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
   * Constructs an empty TLV
   */
  explicit Tlv() {}

  /**
   * Constructs a Tlv with only the tag.
   * @param nTag Tlv tag.
   */
  explicit Tlv(uint16_t nTag);

  /**
   * Constructs a Tlv with a uint8_t value.
   * @param nTag Tlv tag.
   * @param nValue Tlv value.
   */
  explicit Tlv(uint16_t nTag, uint8_t nValue);

  /**
   * Constructs a Tlv with a uint16_t value.
   * @param nTag Tlv tag.
   * @param value Tlv value.
   */
  explicit Tlv(uint16_t nTag, uint16_t value);

  /**
   * Constructs a Tlv with a uint32_t value.
   * @param nTag Tlv tag.
   * @param value Tlv value.
   */
  explicit Tlv(uint16_t nTag, uint32_t value);

  /**
   * Constructs a Tlv with a string value.
   * @param nTag Tlv tag.
   * @param value Tlv value.
   */
  explicit Tlv(uint16_t nTag, const std::string& s);

  /**
   * Constructs a Tlv with an array of m_vValue.
   * @param nTag Tlv tag.
   * @param nLength Length of octet array.
   * @param _m_vValue Array of m_vValue.
   */
  explicit Tlv(uint16_t nTag, uint16_t nLength, const std::vector<uint8_t>& vOctets);

  uint16_t getTag() const;

  uint16_t getLength() const;

  std::vector<uint8_t> getValue() const;

  int size() const;

  void write(Buffer& buffer) const;
  void read(Buffer& buffer);
};

}  // namespace smpp

bool operator==(const smpp::Tlv& lhs, const smpp::Tlv& rhs);

#endif