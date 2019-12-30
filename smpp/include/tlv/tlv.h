#ifndef TLV_H
#define TLV_H

#include <arpa/inet.h>

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
  explicit Tlv(uint16_t nTag, uint16_t nLength, const std::vector<uint8_t>& vValue);

  void setTag(uint16_t nTag);

  void setLength(uint16_t nLength);

  void setValue(const std::vector<uint8_t>& vValue);

  uint16_t getTag() const;

  uint16_t getLength() const;

  std::vector<uint8_t> getValue() const;

  int size() const;

  template <typename Archive>
  void save(Archive& archive) const {
    archive(htons(m_nTag), htons(m_nLength));

    for (auto octet : m_vValue) {
      archive(octet);
    }
  }

  template <class Archive>
  void load(Archive& archive) {
    auto readToHostByteOrder = [&archive](uint16_t& value) {
      uint16_t temp;
      archive(temp);
      value = ntohs(temp);
    };

    readToHostByteOrder(m_nTag);
    readToHostByteOrder(m_nLength);

    for (int i = 0; i < m_nLength; i++) {
      uint8_t octet;
      archive(octet);
      m_vValue.push_back(octet);
    }
  }
};

}  // namespace smpp

bool operator==(const smpp::Tlv& lhs, const smpp::Tlv& rhs);
bool operator!=(const smpp::Tlv& lhs, const smpp::Tlv& rhs);

#endif