#ifndef BASEBIND_H
#define BASEBIND_H

#include <string>

#include "../type/address.h"
#include "pdu_request.h"

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

  std::string getSystemId() const { return m_strSystemId; }
  std::string getPassword() const { return m_strPassword; }
  std::string getSystemType() const { return m_strSystemType; }
  uint8_t getInterfaceVersion() const { return m_nInterfaceVersion; }
  Address getAddress() const { return m_address; }

  void setSystemId(const std::string& strSystemId){m_strSystemId = strSystemId; }
  void setSystemType(const std::string& strSystemType) { m_strSystemType = strSystemType; }
  void setPassword(const std::string& strPassword) { m_strPassword = strPassword; }
  void setInterfaceVersion(uint8_t nInterfaceVersion) { m_nInterfaceVersion = nInterfaceVersion; }
  void setAddress(const Address& newAddress) { m_address = newAddress; }
};

}  // namespace smpp

#endif