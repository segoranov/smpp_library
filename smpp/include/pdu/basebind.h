#ifndef BASEBIND_H
#define BASEBIND_H

#include <cereal/types/base_class.hpp>
#include <string>

#include "pdu_request.h"
#include "type/address.h"

namespace smpp {

class BaseBind : public PduRequest {
 private:
  std::string m_strSystemId;
  std::string m_strPassword;
  std::string m_strSystemType;
  uint8_t m_nInterfaceVersion;
  Address m_address;

 public:
  explicit BaseBind(uint32_t nCommandId);

  std::string getSystemId() const;
  std::string getPassword() const;
  std::string getSystemType() const;
  uint8_t getInterfaceVersion() const;
  Address getAddress() const;

  void setSystemId(const std::string& strSystemId);
  void setSystemType(const std::string& strSystemType);
  void setPassword(const std::string& strPassword);
  void setInterfaceVersion(uint8_t nInterfaceVersion);
  void setAddress(const Address& newAddress);

  template <typename Archive>
  void save(Archive& archive) const {
    archive(cereal::base_class<Pdu>(this));
    auto serializeNullTerminatedStringCharByChar = [&archive](const std::string& str) {
      for (char c : str) {
        archive(c);
      }
      archive('\0');
    };
    serializeNullTerminatedStringCharByChar(m_strSystemId);
    serializeNullTerminatedStringCharByChar(m_strPassword);
    serializeNullTerminatedStringCharByChar(m_strSystemType);
    archive(m_nInterfaceVersion);
    archive(m_address);
  }

  template <typename Archive>
  void load(Archive& archive) {
    archive(cereal::base_class<Pdu>(this));

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

    deserializeNullTerminatedStringCharByChar(m_strSystemId);
    deserializeNullTerminatedStringCharByChar(m_strPassword);
    deserializeNullTerminatedStringCharByChar(m_strSystemType);
    archive(m_nInterfaceVersion);
    archive(m_address);
  }
};  // namespace smpp

}  // namespace smpp

#endif