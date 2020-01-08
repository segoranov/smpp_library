#ifndef PDU_RESPONSE_H
#define PDU_RESPONSE_H

#include "pdu.h"

namespace smpp {

class PduResponse : public Pdu {
 public:
  explicit PduResponse(uint32_t nCommandId);
};

}  // namespace smpp

#endif