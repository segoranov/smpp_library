#include "pdu/pdu.h"

#include <algorithm>

#include "pdu/bind_receiver.h"
#include "pdu/bind_transceiver.h"
#include "pdu/bind_transmitter.h"
#include "pdu/pdu.h"
#include "smpp_exceptions.h"
#include "util/smpp_util.h"

namespace smpp {

Pdu::Pdu(uint32_t nCommandId, bool bIsRequest) : m_bIsRequest{bIsRequest} {
  if (!util::isCommandIdValid(nCommandId)) {
    throw InvalidCommandIdException("Invalid command id while constructing a PDU");
  }

  m_nCommandId = nCommandId;
}

uint32_t Pdu::getCommandLength() const { return m_nCommandLength; }

uint32_t Pdu::getCommandId() const { return m_nCommandId; }

uint32_t Pdu::getCommandStatus() const { return m_nCommandStatus; }

uint32_t Pdu::getSequenceNumber() const { return m_nSequenceNumber; }

std::vector<Tlv> Pdu::getOptionalParameters() const { return m_vOptionalTlvParameters; }

void Pdu::setCommandLength(uint32_t nCommandLength) { m_nCommandLength = nCommandLength; }

void Pdu::setCommandStatus(uint32_t nCommandStatus) { m_nCommandStatus = nCommandStatus; }

void Pdu::setSequenceNumber(uint32_t nSequenceNumber) { m_nSequenceNumber = nSequenceNumber; }

void Pdu::addOptionalParameter(const Tlv& tlv) { m_vOptionalTlvParameters.push_back(tlv); }

bool Pdu::isRequest() const { return m_bIsRequest; }

bool Pdu::isResponse() const { return !m_bIsRequest; }

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
