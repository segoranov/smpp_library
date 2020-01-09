#ifndef SERIALIZATION_UTIL_H
#define SERIALIZATION_UTIL_H

#include <arpa/inet.h>

#include <iostream>

namespace binary {

class BinaryException : public std::exception {
 private:
  std::string m_strError;

 public:
  BinaryException() : m_strError("Default binary exception") {}
  explicit BinaryException(const std::string& strError) : m_strError{strError} {}
  virtual const char* what() const noexcept override { return m_strError.c_str(); }
};

class NotEnoughBytesInStreamException : public BinaryException {
 public:
  NotEnoughBytesInStreamException() : BinaryException{"Not enough bytes in stream"} {}
  explicit NotEnoughBytesInStreamException(const std::string& strError)
      : BinaryException{strError} {}
};

void serializeInt8(uint8_t nValue, std::ostream& os);

void serializeInt16(uint16_t nValue, std::ostream& os);

void serializeInt32(uint32_t nValue, std::ostream& os);

void serializeNullTerminatedString(const std::string& str, std::ostream& os);

void serializeOctetString(const std::string& str, std::ostream& os);

void serializeChar(char ch, std::ostream& os);

uint8_t deserializeInt8(std::istream& is);

uint16_t deserializeInt16(std::istream& is);

uint32_t deserializeInt32(std::istream& is);

std::string deserializeNullTerminatedString(std::istream& is);

std::string deserializeOctetString(int size, std::istream& is);

char deserializeChar(std::istream& is);

}  // namespace binary

#endif