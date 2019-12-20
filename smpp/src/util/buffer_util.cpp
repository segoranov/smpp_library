#include "util/buffer_util.h"

#include <algorithm>
#include <iomanip>

namespace smpp::buffer_util {

// TODO SG Throwing exceptions??

Tlv readTlv(Buffer& buffer) {
  Tlv tlv;
  tlv.read(buffer);
  return tlv;
}

void writeTlv(Buffer& buffer, const Tlv& tlv) { tlv.write(buffer); }

Address readAddress(Buffer& buffer) {
  auto address = Address{};
  address.read(buffer);
  return address;
}

void writeAddress(Buffer& buffer, const Address& address) { address.write(buffer); }



}  // namespace smpp::buffer_util
