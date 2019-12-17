#include "../include/type/address.h"

namespace smpp {

Address::Address(uint8_t addr_ton, uint8_t addr_npi, std::string address_range)
    : addr_ton{addr_ton}, addr_npi{addr_npi}, address_range{address_range} {}

int Address::size() const {
  return 2 + address_range.size() + 1;  // + 1 because of the null terminated string; TODO SG
                                        // figure out a way to represent null terminated strings
}

void Address::read(Buffer& buffer) {
  addr_ton = buffer.readInt8();
  addr_npi = buffer.readInt8();
  address_range = buffer.readNullTerminatedString();
}

void Address::write(Buffer& buffer) const {
  buffer.writeInt8(addr_ton);
  buffer.writeInt8(addr_npi);
  buffer.writeNullTerminatedString(address_range.c_str());
}

}  // namespace smpp

bool operator==(const smpp::Address& lhs, const smpp::Address& rhs) {
  return lhs.getAddrTon() == rhs.getAddrTon() && lhs.getAddrNpi() == rhs.getAddrNpi() &&
         lhs.getAddressRange() == rhs.getAddressRange();
}