#ifndef PDU_REUQEST_H
#define PDU_REQUEST_H

#include "pdu.h"

namespace smpp {

class PduRequest : public Pdu {
 public:
  PduRequest(uint32_t nCommandId);
};

}  // namespace smpp

#endif