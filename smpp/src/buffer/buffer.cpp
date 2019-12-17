#include "../include/buffer/buffer.h"

#include <iostream>

namespace smpp {

Buffer::Buffer() : m_stringBuffer(""), m_stream{&m_stringBuffer} {};

void Buffer::resetReadMarker() { m_stream.seekg(0, m_stream.beg); }

void Buffer::writeInt8(uint8_t nValue) {
  m_stream.write(reinterpret_cast<char*>(&nValue), sizeof(uint8_t));
}

void Buffer::writeInt16(uint16_t nValue) {
  m_stream.write(reinterpret_cast<char*>(&nValue), sizeof(uint16_t));
}

void Buffer::writeInt32(uint32_t nValue) {
  m_stream.write(reinterpret_cast<char*>(&nValue), sizeof(uint32_t));
}

void Buffer::writeNullTerminatedString(const char* str) {
  writeOctetString(str);
  writeChar('\0');
}

void Buffer::writeNullTerminatedString(const std::string& str) {
  writeOctetString(str);
  writeChar('\0');
}

void Buffer::writeOctetString(const std::string& str) {
  m_stream.write(str.c_str(), str.size());
}

void Buffer::writeChar(char ch) { m_stream.write(&ch, sizeof(char)); }

uint8_t Buffer::readInt8() {
  uint8_t nValue;
  m_stream.read(reinterpret_cast<char*>(&nValue), sizeof(uint8_t));
  return nValue;
}

uint16_t Buffer::readInt16() {
  uint16_t nValue;
  m_stream.read(reinterpret_cast<char*>(&nValue), sizeof(uint16_t));
  return nValue;
}

uint32_t Buffer::readInt32() {
  uint32_t nValue;
  m_stream.read(reinterpret_cast<char*>(&nValue), sizeof(uint32_t));
  return nValue;
}

std::string Buffer::readNullTerminatedString() {
  std::string str;
  char ch;
  while ((ch = readChar()) != '\0') {
    str += ch;
  }
  return str;
}

std::string Buffer::readString(int size) {
  std::string str;
  for (int i = 0; i < size; i++) {
    str += readChar();
  }
  return str;
}

char Buffer::readChar() {
  char ch;
  m_stream.read(&ch, sizeof(char));
  return ch;
}

}  // namespace smpp
