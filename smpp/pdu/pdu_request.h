#ifndef PDU_REUQEST_H
#define PDU_REQUEST_H

#include "pdu.h"

namespace smpp {

class PduRequest : public Pdu {
 private:
 public:
    PduRequest(const PduHeader& pduHeader);
    
};

}

#endif