#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>

#include "buffer/buffer.h"

namespace smpp {

/**
 * Representation of an Address in SMPP
 */
class Address {
 private:
  uint8_t addr_ton;
  uint8_t addr_npi;
  std::string address_range;

 public:
  Address(uint8_t addr_ton = 0, uint8_t addr_npi = 0, std::string address_range = "");

  uint8_t getAddrTon() const;
  uint8_t getAddrNpi() const;
  std::string getAddressRange() const;

  void setAddrTon(uint8_t value);
  void setAddrNpi(uint8_t value);
  void setAddressRange(const std::string& value);

  /**
   * @return size in bytes
   */
  int size() const;
};

}  // namespace smpp

bool operator==(const smpp::Address& lhs, const smpp::Address& rhs);

#endif