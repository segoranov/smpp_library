#ifndef BASEBIND_H
#define BASEBIND_H

#include "pdu_request.h"

namespace smpp {

class BaseBind : public PduRequest {
 public:
  explicit BaseBind(uint32_t nCommandId);
};

}  // namespace smpp

#endif