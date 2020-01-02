#ifndef BASE_BIND_H
#define BASE_BIND_H

#include <cereal/types/base_class.hpp>
#include <string>

#include "pdu_request.h"
#include "type/address.h"
#include "util/serialization_util.h"

namespace smpp {

class BaseBind : public PduRequest {
 private:
  std::string m_strSystemId;
  std::string m_strPassword;
  std::string m_strSystemType;
  uint8_t m_nInterfaceVersion;
  Address m_address;

 protected:
  virtual void serializeBody(std::ostream& os) const final;

  virtual void deserializeAfterCommandId(std::istream& is) final;

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
};

}  // namespace smpp

#endif