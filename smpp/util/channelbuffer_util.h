#ifndef CHANNEL_BUFFER_UTIL_H
#define CHANNEL_BUFFER_UTIL_H

#include "../tlv/tlv.h"
#include "../transcoder/channel_buffer.h"
#include "../type/address.h"

namespace smpp::channelbuffer_util {

// TODO SG Throwing exceptions??

Tlv readTlv(ChannelBuffer& buffer);

void writeTlv(ChannelBuffer& buffer, const Tlv& tlv);

Address readAddress(ChannelBuffer& buffer);

void writeAddress(ChannelBuffer& buffer, const Address& address);

}  // namespace smpp::channelbuffer_util

#endif