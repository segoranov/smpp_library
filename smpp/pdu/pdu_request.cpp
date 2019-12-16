#include "pdu_request.h"

namespace smpp {

PduRequest::PduRequest(uint32_t nCommandId) : Pdu{nCommandId, true} {}

}  // namespace smpp