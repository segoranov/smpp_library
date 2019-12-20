#ifndef BUFFER_UTIL_H
#define BUFFER_UTIL_H

#include "buffer/buffer.h"
#include "tlv/tlv.h"
#include "type/address.h"

namespace smpp::buffer_util {

// TODO SG Throwing exceptions??

Tlv readTlv(Buffer& buffer);

void writeTlv(Buffer& buffer, const Tlv& tlv);

Address readAddress(Buffer& buffer);

void writeAddress(Buffer& buffer, const Address& address);

}  // namespace smpp::buffer_util

#endif