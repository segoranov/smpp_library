#ifndef ADDRESS_H
#define ADDRES_H

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

  uint8_t getAddrTon() const { return addr_ton; }
  uint8_t getAddrNpi() const { return addr_npi; }
  std::string getAddressRange() const { return address_range; }

  void setAddrTon(uint8_t value) { addr_ton = value; }
  void setAddrNpi(uint8_t value) { addr_npi = value; }
  void setAddressRange(const std::string& value) { address_range = value; }

  /**
   * @return size in bytes
   */
  int size() const;

  void read(Buffer& buffer);

  void write(Buffer& buffer) const;

};  // namespace smpp

}  // namespace smpp

bool operator==(const smpp::Address& lhs, const smpp::Address& rhs);

#endif