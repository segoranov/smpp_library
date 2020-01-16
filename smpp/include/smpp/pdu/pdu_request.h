#ifndef PDU_REQUEST_H
#define PDU_REQUEST_H

#include "pdu.h"

namespace smpp {

class PduRequest : public Pdu {
 public:
  explicit PduRequest(uint32_t nCommandId);

  using Ptr = std::unique_ptr<PduRequest>;
};

}  // namespace smpp

#endif