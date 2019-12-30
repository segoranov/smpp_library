#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>

namespace smpp {

/**
 * Representation of an Address in SMPP
 */
class Address {
 private:
  uint8_t addr_ton;
  uint8_t addr_npi;
  std::string address_range;

 public:
  Address(uint8_t addr_ton = 0, uint8_t addr_npi = 0, std::string address_range = "");

  uint8_t getAddrTon() const;
  uint8_t getAddrNpi() const;
  std::string getAddressRange() const;

  void setAddrTon(uint8_t value);
  void setAddrNpi(uint8_t value);
  void setAddressRange(const std::string& value);

  /**
   * @return size in bytes
   */
  int size() const;

  template <typename Archive>
  void save(Archive& archive) const {
    archive(addr_ton);
    archive(addr_npi);

    auto serializeNullTerminatedStringCharByChar = [&archive](const std::string& str) {
      for (char c : str) {
        archive(c);
      }
      archive('\0');
    };

    serializeNullTerminatedStringCharByChar(address_range);
  }

  template <typename Archive>
  void load(Archive& archive) {
    archive(addr_ton);
    archive(addr_npi);

    auto deserializeNullTerminatedStringCharByChar = [&archive](std::string& str) {
      str = "";
      char c = 'A';
      while (true) {  // TODO SG: Probably not the best thing to do while (true) ...
        archive(c);
        if (c == '\0') {  // std::string adds by default '\0' at the end
          break;
        }
        str += c;
      }
    };

    deserializeNullTerminatedStringCharByChar(address_range);
  }
};

}  // namespace smpp

bool operator==(const smpp::Address& lhs, const smpp::Address& rhs);
bool operator!=(const smpp::Address& lhs, const smpp::Address& rhs);

#endif