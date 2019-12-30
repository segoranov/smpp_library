#include "type/address.h"

#include "util/serialization_util.h"

namespace smpp {

Address::Address(uint8_t addr_ton, uint8_t addr_npi, std::string address_range)
    : addr_ton{addr_ton}, addr_npi{addr_npi}, address_range{address_range} {}

int Address::size() const {
  return 2 + address_range.size() +
         1;  // + 1 because address_range is C-octet string (null terminated)
}

void Address::serialize(std::ostream& os) const {
  binary::serializeInt8(addr_ton, os);
  binary::serializeInt8(addr_npi, os);
  binary::serializeNullTerminatedString(address_range, os);
}

void Address::deserialize(std::istream& is) {
  addr_ton = binary::deserializeInt8(is);
  addr_npi = binary::deserializeInt8(is);
  address_range = binary::deserializeNullTerminatedString(is);
}

uint8_t Address::getAddrTon() const { return addr_ton; }

uint8_t Address::getAddrNpi() const { return addr_npi; }

std::string Address::getAddressRange() const { return address_range; }

void Address::setAddrTon(uint8_t value) { addr_ton = value; }

void Address::setAddrNpi(uint8_t value) { addr_npi = value; }

void Address::setAddressRange(const std::string& value) { address_range = value; }

}  // namespace smpp

bool operator==(const smpp::Address& lhs, const smpp::Address& rhs) {
  return lhs.getAddrTon() == rhs.getAddrTon() && lhs.getAddrNpi() == rhs.getAddrNpi() &&
         lhs.getAddressRange() == rhs.getAddressRange();
}

bool operator!=(const smpp::Address& lhs, const smpp::Address& rhs) { return !(lhs == rhs); }