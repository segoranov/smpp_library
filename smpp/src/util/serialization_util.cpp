#include "util/serialization_util.h"

namespace binary {

void serializeInt8(uint8_t nValue, std::ostream& os) {
  os.write(reinterpret_cast<char*>(&nValue), sizeof(uint8_t));
}

void serializeInt16(uint16_t nValue, std::ostream& os) {
  nValue = htons(nValue);
  os.write(reinterpret_cast<char*>(&nValue), sizeof(uint16_t));
}

void serializeInt32(uint32_t nValue, std::ostream& os) {
  nValue = htonl(nValue);
  os.write(reinterpret_cast<char*>(&nValue), sizeof(uint32_t));
}

void serializeNullTerminatedString(const std::string& str, std::ostream& os) {
  serializeOctetString(str, os);
  serializeChar('\0', os);
}

void serializeOctetString(const std::string& str, std::ostream& os) {
  os.write(str.c_str(), str.size());
}

void serializeChar(char ch, std::ostream& os) { os.put(ch); }

uint8_t deserializeInt8(std::istream& is) {
  uint8_t nValue;
  is.read(reinterpret_cast<char*>(&nValue), sizeof(uint8_t));
  return nValue;
}

uint16_t deserializeInt16(std::istream& is) {
  uint16_t nValue;
  is.read(reinterpret_cast<char*>(&nValue), sizeof(uint16_t));
  return ntohs(nValue);
}

uint32_t deserializeInt32(std::istream& is) {
  uint32_t nValue;
  is.read(reinterpret_cast<char*>(&nValue), sizeof(uint32_t));
  return ntohl(nValue);
}

std::string deserializeNullTerminatedString(std::istream& is) {
  std::string str;
  char ch;
  while ((ch = deserializeChar(is)) != '\0') {
    str += ch;
  }
  return str;
}

std::string deserializeOctetString(int size, std::istream& is) {
  std::string str;
  for (int i = 0; i < size; i++) {
    str += deserializeChar(is);
  }
  return str;
}

char deserializeChar(std::istream& is) { return is.get(); }

}  // namespace binary