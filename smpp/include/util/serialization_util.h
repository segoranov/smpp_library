#ifndef SERIALIZATION_UTIL_H
#define SERIALIZATION_UTIL_H

#include <arpa/inet.h>

#include <iostream>

namespace binary {

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