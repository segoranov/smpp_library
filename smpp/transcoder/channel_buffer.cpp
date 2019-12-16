#include "channel_buffer.h"

#include <iostream>

namespace smpp {

ChannelBuffer::ChannelBuffer() : m_stringBuffer(""), m_stream{&m_stringBuffer} {};

void ChannelBuffer::resetMarker() { m_stream.seekg(0, m_stream.beg); }

void ChannelBuffer::writeInt8(uint8_t nValue) {
  m_stream.write(reinterpret_cast<char*>(&nValue), sizeof(uint8_t));
}

uint8_t ChannelBuffer::readInt8() {
  uint8_t nValue;
  m_stream.read(reinterpret_cast<char*>(&nValue), sizeof(uint8_t));
  return nValue;
}

void ChannelBuffer::writeInt16(uint16_t nValue) {
  m_stream.write(reinterpret_cast<char*>(&nValue), sizeof(uint16_t));
}

uint16_t ChannelBuffer::readInt16() {
  uint16_t nValue;
  m_stream.read(reinterpret_cast<char*>(&nValue), sizeof(uint16_t));
  return nValue;
}

void ChannelBuffer::writeInt32(uint32_t nValue) {
  m_stream.write(reinterpret_cast<char*>(&nValue), sizeof(uint32_t));
}

uint32_t ChannelBuffer::readInt32() {
  uint32_t nValue;
  m_stream.read(reinterpret_cast<char*>(&nValue), sizeof(uint32_t));
  return nValue;
}

}  // namespace smpp
