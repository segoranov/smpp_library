#include "../include/buffer/buffer.h"

#include <arpa/inet.h>

#include <iostream>

namespace smpp {

Buffer::Buffer() : m_stringBuffer(""), m_stream{&m_stringBuffer} {};

void Buffer::resetReadMarker() { m_stream.seekg(0, m_stream.beg); }

void Buffer::writeInt8(uint8_t nValue) {
  m_stream.write(reinterpret_cast<char*>(&nValue), sizeof(uint8_t));
}

void Buffer::writeInt16(uint16_t nValue) {
  nValue = htons(nValue);
  m_stream.write(reinterpret_cast<char*>(&nValue), sizeof(uint16_t));
}

void Buffer::writeInt32(uint32_t nValue) {
  nValue = htonl(nValue);
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

void Buffer::writeOctetString(const std::string& str) { m_stream.write(str.c_str(), str.size()); }

void Buffer::writeChar(char ch) { m_stream.put(ch); }

uint8_t Buffer::readInt8() {
  uint8_t nValue;
  m_stream.read(reinterpret_cast<char*>(&nValue), sizeof(uint8_t));
  return nValue;
}

uint16_t Buffer::readInt16() {
  uint16_t nValue;
  m_stream.read(reinterpret_cast<char*>(&nValue), sizeof(uint16_t));
  return ntohs(nValue);
}

uint32_t Buffer::readInt32() {
  uint32_t nValue;
  m_stream.read(reinterpret_cast<char*>(&nValue), sizeof(uint32_t));
  return ntohl(nValue);
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

char Buffer::readChar() { return m_stream.get(); }

void Buffer::skip(int numberOfBytesToSkip) { m_stream.seekg(numberOfBytesToSkip, m_stream.cur); } // TODO SG Unit test

int Buffer::readableBytes() const {
  return 0; // TODO SG + unit test
}

}  // namespace smpp
