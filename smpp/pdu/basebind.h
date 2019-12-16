#ifndef BASEBIND_H
#define BASEBIND_H

#include <string>

#include "pdu_request.h"
#include "../type/address.h"

namespace smpp {

class BaseBind : public PduRequest {
 private:
  std::string m_strSystemId;
  std::string m_strPassword;
  std::string m_strSystemType;
  uint8_t m_nInterfaceVersion;
  Address address;

 public:
  explicit BaseBind(uint32_t nCommandId);
};

}  // namespace smpp

#endif