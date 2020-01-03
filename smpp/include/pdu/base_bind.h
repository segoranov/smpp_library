#ifndef BASE_BIND_H
#define BASE_BIND_H

#include <cereal/types/base_class.hpp>
#include <string>

#include "pdu_request.h"
#include "util/serialization_util.h"

namespace smpp {

class BaseBind : public PduRequest {
 private:
  std::string m_strSystemId;
  std::string m_strPassword;
  std::string m_strSystemType;
  uint8_t m_nInterfaceVersion;
  uint8_t m_nAddrTon;
  uint8_t m_nAddrNpi;
  std::string m_strAddressRange;

 protected:
  virtual void serializeBody(std::ostream& os) const final;
  virtual void deserializeBody(std::istream& is) final;

 public:
  explicit BaseBind(uint32_t nCommandId);

  std::string getSystemId() const;
  std::string getPassword() const;
  std::string getSystemType() const;
  uint8_t getInterfaceVersion() const;
  uint8_t getAddrTon() const;
  uint8_t getAddrNpi() const;
  std::string getAddressRange() const;

  void setSystemId(const std::string& strSystemId);
  void setSystemType(const std::string& strSystemType);
  void setPassword(const std::string& strPassword);
  void setInterfaceVersion(uint8_t nInterfaceVersion);
  void setAddrTon(uint8_t value);
  void setAddrNpi(uint8_t value);
  void setAddressRange(const std::string& value);
};

}  // namespace smpp

#endif