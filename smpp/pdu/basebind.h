#ifndef BASEBIND_H
#define BASEBIND_H

#include <string>

#include "pdu_request.h"

namespace smpp {

class BaseBind : public PduRequest {
 private:
  std::string systemId;
  std::string password;
  std::string systemType;
  uint8_t interfaceVersion;

 public:
  explicit BaseBind(uint32_t nCommandId);
};

}  // namespace smpp

#endif