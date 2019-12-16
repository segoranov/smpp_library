#include "pdu.h"

#include <algorithm>

namespace smpp {

PduHeader::PduHeader(uint32_t nCommandLength, uint32_t nCommandID, uint32_t nCommandStatus,
                     uint32_t nSequenceNumber)
    : m_nCommandLength{nCommandLength},
      m_nCommandID{nCommandID},
      m_nCommandStatus{nCommandStatus},
      m_nSequenceNumber{nSequenceNumber} {}

Pdu::Pdu(PduHeader pduHeader, bool isRequest) : m_pduHeader{pduHeader}, m_bIsRequest{isRequest} {}

void Pdu::addOptionalParameter(Tlv tlv) { m_vOptionalTlvParameters.push_back(tlv); }

std::optional<Tlv> Pdu::removeOptionalParameter(uint16_t nTag) {
  auto result = std::find_if(m_vOptionalTlvParameters.begin(), m_vOptionalTlvParameters.end(),
                             [nTag](Tlv tlv) { return tlv.getTag() == nTag; });
  return result != m_vOptionalTlvParameters.end() ? std::optional<Tlv>{*result} : std::nullopt;
}

}  // namespace smpp