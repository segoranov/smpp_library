#include "channelbuffer_util.h"

namespace smpp::channelbuffer_util {

// TODO SG Throwing exceptions??

Tlv readTlv(ChannelBuffer& buffer) {}

void writeTlv(ChannelBuffer& buffer, const Tlv& tlv) {}

Address readAddress(ChannelBuffer& buffer) {
  auto address = Address{};
  address.read(buffer);
  return address;
}

void writeAddress(ChannelBuffer& buffer, const Address& address) { address.write(buffer); }

}  // namespace smpp::channelbuffer_util
