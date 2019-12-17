#include "../include/pdu/pdu.h"

#include <algorithm>

#include "../include/buffer/buffer.h"
#include "../include/util/buffer_util.h"

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

void Pdu::readOptionalParameters(Buffer& buffer) {
  // if there is any data left, it's part of an optional parameter
  while (buffer.areThereMoreBytesToRead()) {
    auto tlv = buffer_util::readTlv(buffer);
    addOptionalParameter(tlv);
  }
}

void Pdu::writeOptionalParameters(Buffer& buffer) {
  std::for_each(m_vOptionalTlvParameters.begin(), m_vOptionalTlvParameters.end(),
                [&buffer](const Tlv& tlv) { buffer_util::writeTlv(buffer, tlv); });
}

}  // namespace smpp