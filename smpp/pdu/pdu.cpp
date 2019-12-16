#include "pdu.h"

namespace smpp {
Pdu::Pdu(uint32_t nCommandLength, uint32_t nCommandID, uint32_t nCommandStatus,
         uint32_t nSequenceNumber)
    : m_nCommandLength{nCommandLength},
      m_nCommandID{nCommandID},
      m_nCommandStatus{nCommandStatus},
      m_nSequenceNumber{nSequenceNumber} {}

}  // namespace smpp