#include "pdu.h"

#include <algorithm>

namespace smpp {

Pdu::Pdu(uint32_t nCommandId, bool bIsRequest)
    : m_nCommandId{nCommandId}, m_bIsRequest{bIsRequest} {}

void Pdu::addOptionalParameter(const Tlv& tlv) { m_vOptionalTlvParameters.push_back(tlv); }

std::optional<Tlv> Pdu::removeOptionalParameter(uint16_t nTag) {
  auto iterTlvToRemove =
      std::find_if(m_vOptionalTlvParameters.begin(), m_vOptionalTlvParameters.end(),
                   [&nTag](Tlv tlv) { return tlv.getTag() == nTag; });

  if (iterTlvToRemove == m_vOptionalTlvParameters.end()) {
    return std::nullopt;
  }

  auto tlvToRemove = *iterTlvToRemove;
  m_vOptionalTlvParameters.erase(iterTlvToRemove);
  return tlvToRemove;
}

bool Pdu::hasOptionalParameter(uint16_t nTag) const {
  auto iterTlv = std::find_if(m_vOptionalTlvParameters.begin(), m_vOptionalTlvParameters.end(),
                              [nTag](Tlv tlv) { return tlv.getTag() == nTag; });
  return iterTlv != m_vOptionalTlvParameters.end();
}

}  // namespace smpp