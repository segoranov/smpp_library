#include "util/buffer_util.h"

#include <algorithm>
#include <iomanip>

namespace smpp::buffer_util {

// TODO SG Throwing exceptions??

Tlv readTlv(Buffer& buffer) {
  Tlv tlv;
  tlv.setTag(buffer.readInt16());
  tlv.setLength(buffer.readInt16());

  std::vector<uint8_t> tlvValue;
  for (int i = 0; i < tlv.getLength(); i++) {
    tlvValue.push_back(buffer.readInt8());
  }
  tlv.setValue(tlvValue);

  return tlv;
}

void writeTlv(Buffer& buffer, const Tlv& tlv) {
  buffer.writeInt16(tlv.getTag());
  buffer.writeInt16(tlv.getLength());

  auto tlvValue = tlv.getValue();
  std::for_each(tlvValue.begin(), tlvValue.end(),
                [&buffer](uint8_t octet) { buffer.writeInt8(octet); });
}

Address readAddress(Buffer& buffer) {
  auto address = Address{};
  address.setAddrTon(buffer.readInt8());
  address.setAddrNpi(buffer.readInt8());
  address.setAddressRange(buffer.readNullTerminatedString());
  return address;
}

void writeAddress(Buffer& buffer, const Address& address) {
  buffer.writeInt8(address.getAddrTon());
  buffer.writeInt8(address.getAddrNpi());
  buffer.writeNullTerminatedString(address.getAddressRange());
}

}  // namespace smpp::buffer_util
