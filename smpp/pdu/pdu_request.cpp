#include "pdu_request.h"

namespace smpp {

PduRequest::PduRequest(const PduHeader& pduHeader) : Pdu{pduHeader, true} {

}

}