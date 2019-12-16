#include "channel_buffer.h"

#include <iostream>

namespace smpp {

ChannelBuffer::ChannelBuffer() : m_stringBuffer(""), m_stream{&m_stringBuffer} {};

void ChannelBuffer::resetReadMarker() { m_stream.seekg(0, m_stream.beg); }

void ChannelBuffer::writeInt8(uint8_t nValue) {
  m_stream.write(reinterpret_cast<char*>(&nValue), sizeof(uint8_t));
}

void ChannelBuffer::writeInt16(uint16_t nValue) {
  m_stream.write(reinterpret_cast<char*>(&nValue), sizeof(uint16_t));
}

void ChannelBuffer::writeInt32(uint32_t nValue) {
  m_stream.write(reinterpret_cast<char*>(&nValue), sizeof(uint32_t));
}

void ChannelBuffer::writeNullTerminatedString(const char* str) {
  writeOctetString(std::string{str});
  writeChar('\0');
}

void ChannelBuffer::writeOctetString(const std::string& str) {
  m_stream.write(str.c_str(), str.size());
}

void ChannelBuffer::writeChar(char ch) { m_stream.write(&ch, sizeof(char)); }

uint8_t ChannelBuffer::readInt8() {
  uint8_t nValue;
  m_stream.read(reinterpret_cast<char*>(&nValue), sizeof(uint8_t));
  return nValue;
}

uint16_t ChannelBuffer::readInt16() {
  uint16_t nValue;
  m_stream.read(reinterpret_cast<char*>(&nValue), sizeof(uint16_t));
  return nValue;
}

uint32_t ChannelBuffer::readInt32() {
  uint32_t nValue;
  m_stream.read(reinterpret_cast<char*>(&nValue), sizeof(uint32_t));
  return nValue;
}

std::string ChannelBuffer::readNullTerminatedString() {
  std::string str;
  char ch;
  while ((ch = readChar()) != '\0') {
    str += ch;
  }
  return str;
}

std::string ChannelBuffer::readString(int size) {
  std::string str;
  for (int i = 0; i < size; i++) {
    str += readChar();
  }
  return str;
}

char ChannelBuffer::readChar() {
  char ch;
  m_stream.read(&ch, sizeof(char));
  return ch;
}

}  // namespace smpp
