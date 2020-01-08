#include "smpp/pdu/pdu_response.h"

namespace smpp {

PduResponse::PduResponse(uint32_t nCommandId) : Pdu{nCommandId, false} {}

}  // namespace smpp