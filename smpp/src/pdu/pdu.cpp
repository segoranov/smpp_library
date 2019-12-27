#include "pdu/pdu.h"

#include <algorithm>

#include "buffer/buffer.h"
#include "pdu/bindreceiver.h"
#include "pdu/bindtransceiver.h"
#include "pdu/bindtransmitter.h"
#include "pdu/pdu.h"
#include "smppexceptions.h"
#include "util/buffer_util.h"

namespace smpp {

Pdu::Pdu(uint32_t nCommandId, bool bIsRequest)
    : m_nCommandId{nCommandId}, m_bIsRequest{bIsRequest} {}

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

void Pdu::readOptionalParameters(Buffer& buffer) {
  // if there is any data left, it's part of an optional parameter
  while (buffer.areThereMoreBytesToRead()) {
    auto tlv = buffer_util::readTlv(buffer);
    addOptionalParameter(tlv);
  }
}

void Pdu::writeOptionalParameters(Buffer& buffer) const {
  std::for_each(m_vOptionalTlvParameters.begin(), m_vOptionalTlvParameters.end(),
                [&buffer](const Tlv& tlv) { buffer_util::writeTlv(buffer, tlv); });
}

std::unique_ptr<Pdu> Pdu::createPduByCommandId(uint32_t nCommandId) {
  switch (nCommandId) {
    case constants::CMD_ID_BIND_TRANSMITTER: {
      return std::make_unique<BindTransmitter>();
    }
    case constants::CMD_ID_BIND_TRANSCEIVER: {
      return std::make_unique<BindTransceiver>();
    }
    case constants::CMD_ID_BIND_RECEIVER: {
      return std::make_unique<BindReceiver>();
    }
    default: {
      throw InvalidCommandIdException();
    }
  }
}

}  // namespace smpp