#ifndef BASEBIND_H
#define BASEBIND_H

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

 protected:
  virtual void readBody(Buffer& buffer) override;
  virtual void writeBody(Buffer& buffer) const override;
};

}  // namespace smpp

#endif