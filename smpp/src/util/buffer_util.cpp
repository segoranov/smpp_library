#include "util/buffer_util.h"

namespace smpp::buffer_util {

// TODO SG Throwing exceptions??

Tlv readTlv(Buffer& buffer) {}

void writeTlv(Buffer& buffer, const Tlv& tlv) {}

Address readAddress(Buffer& buffer) {
  auto address = Address{};
  address.read(buffer);
  return address;
}

void writeAddress(Buffer& buffer, const Address& address) { address.write(buffer); }

}  // namespace smpp::buffer_util
