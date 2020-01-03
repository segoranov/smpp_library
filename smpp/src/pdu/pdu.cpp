#include "pdu/pdu.h"

#include <algorithm>
#include <unordered_map>

#include "pdu/bind_receiver.h"
#include "pdu/bind_transceiver.h"
#include "pdu/bind_transmitter.h"
#include "pdu/bind_transmitter_resp.h"
#include "pdu/pdu.h"
#include "smpp_constants.h"
#include "smpp_exceptions.h"
#include "util/serialization_util.h"
#include "util/smpp_util.h"

namespace smpp {

/**
 * Construct On First Use Idiom:
 * https://isocpp.org/wiki/faq/ctors#static-init-order
 * https://isocpp.org/wiki/faq/ctors#static-init-order-on-first-use
 * https://isocpp.org/wiki/faq/ctors#construct-on-first-use-v2
 */
const std::unordered_map<uint32_t, Pdu::BodyFactory>& getCommandIdToBodyFactoryMap() {
  static const std::unordered_map<uint32_t, Pdu::BodyFactory>* const commandIdToFactoryMap =
      new std::unordered_map<uint32_t, Pdu::BodyFactory>{
          {constants::CMD_ID_BIND_RECEIVER, BindReceiver::createPduBody},
          {constants::CMD_ID_BIND_TRANSMITTER, BindTransmitter::createPduBody},
          {constants::CMD_ID_BIND_TRANSMITTER_RESP, BindTransmitterResp::createPduBody},
          {constants::CMD_ID_BIND_TRANSCEIVER, BindTransceiver::createPduBody},
      };
  return *commandIdToFactoryMap;
}

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

bool Pdu::isRequest() const { return m_bIsRequest; }

bool Pdu::isResponse() const { return !m_bIsRequest; }

bool Pdu::hasOptionalParameter(uint16_t nTag) const {
  auto iterTlv = std::find_if(m_vOptionalTlvParameters.begin(), m_vOptionalTlvParameters.end(),
                              [nTag](Tlv tlv) { return tlv.getTag() == nTag; });
  return iterTlv != m_vOptionalTlvParameters.end();
}

void Pdu::serializeHeader(std::ostream& os) const {
  if (!util::isCommandLengthValid(m_nCommandLength)) {
    std::stringstream error;
    error << "Invalid command length detected during Pdu serialization - [" << m_nCommandLength
          << "]";
    throw InvalidCommandLengthException(error.str());
  }

  if (!util::isCommandIdValid(m_nCommandId)) {
    std::stringstream error;
    error << "Invalid command id detected during Pdu serialization - [" << m_nCommandId << "]";
    throw InvalidCommandIdException(error.str());
  }

  // TODO SG: validate command status and sequence number

  binary::serializeInt32(m_nCommandLength, os);
  binary::serializeInt32(m_nCommandId, os);
  binary::serializeInt32(m_nCommandStatus, os);
  binary::serializeInt32(m_nSequenceNumber, os);
}

void Pdu::serializeOptionalParameters(std::ostream& os) const {
  for (const auto& tlv : m_vOptionalTlvParameters) {
    tlv.serialize(os);
  }
}

std::unique_ptr<Pdu> Pdu::deserialize(std::istream& is) {
  // 1. Deserialize all 4 PDU header fields
  const uint32_t nCommandLength = binary::deserializeInt32(is);
  if (!util::isCommandLengthValid(nCommandLength)) {
    std::stringstream error;
    error << "Invalid command length detected during Pdu deserialization - [" << nCommandLength
          << "]";
    throw InvalidCommandLengthException(error.str());
  }

  const uint32_t nCommandId = binary::deserializeInt32(is);
  if (!util::isCommandIdValid(nCommandId)) {
    std::stringstream error;
    error << "Invalid command id parsed detected Pdu deserialization - [" << nCommandId << "]";
    throw InvalidCommandIdException(error.str());
  }

  // TODO SG validate
  const uint32_t nCommandStatus = binary::deserializeInt32(is);

  const uint32_t nSequenceNumber = binary::deserializeInt32(is);

  // 2. Deserialize PDU body
  auto deserializedPdu = getCommandIdToBodyFactoryMap().at(nCommandId)(is);

  // 3. Set header fields
  deserializedPdu->m_nCommandLength = nCommandLength;
  deserializedPdu->m_nCommandStatus = nCommandStatus;
  deserializedPdu->m_nSequenceNumber = nSequenceNumber;

  return deserializedPdu;
}

}  // namespace smpp
