#include "smpp/pdu/pdu.h"

#include <algorithm>
#include <sstream>
#include <unordered_map>

#include "smpp/commands.h"
#include "smpp/smpp_constants.h"
#include "smpp/smpp_exceptions.h"
#include "smpp/util/logging.h"
#include "smpp/util/serialization_util.h"
#include "smpp/util/smpp_util.h"

namespace smpp {

/**
 * Construct On First Use Idiom:
 * https://isocpp.org/wiki/faq/ctors#static-init-order
 * https://isocpp.org/wiki/faq/ctors#static-init-order-on-first-use
 * https://isocpp.org/wiki/faq/ctors#construct-on-first-use-v2
 */
const std::unordered_map<uint32_t, Pdu::Factory>& getCommandIdToFactoryMap() {
  static const std::unordered_map<uint32_t, Pdu::Factory>* const commandIdToFactoryMap =
      new std::unordered_map<uint32_t, Pdu::Factory>{
          {constants::CMD_ID_BIND_RECEIVER, BindReceiver::create},
          {constants::CMD_ID_BIND_TRANSMITTER, BindTransmitter::create},
          {constants::CMD_ID_BIND_TRANSMITTER_RESP, BindTransmitterResp::create},
          {constants::CMD_ID_BIND_TRANSCEIVER, BindTransceiver::create},
          {constants::CMD_ID_SUBMIT_SM, SubmitSm::create},
          {constants::CMD_ID_SUBMIT_SM_RESP, SubmitSmResp::create},
          {constants::CMD_ID_DATA_SM, DataSm::create},
          {constants::CMD_ID_OUTBIND, Outbind::create},
          {constants::CMD_ID_SUBMIT_MULTI, SubmitMulti::create},
          {constants::CMD_ID_DELIVER_SM, DeliverSm::create},
      };
  return *commandIdToFactoryMap;
}

Pdu::Pdu(uint32_t nCommandId) {
  INFO << "Pdu::Pdu() constructor";
  if (!util::isCommandIdValid(nCommandId)) {
    std::stringstream error;
    error << "Invalid command id while constructing a PDU - [ " << nCommandId << "]";
    throw InvalidCommandIdException();
  }
  m_nCommandId = nCommandId;
}

uint32_t Pdu::getCommandLength() const { return m_nCommandLength; }

uint32_t Pdu::getCommandId() const { return m_nCommandId; }

uint32_t Pdu::getCommandStatus() const { return m_nCommandStatus; }

uint32_t Pdu::getSequenceNumber() const { return m_nSequenceNumber; }

std::vector<Tlv> Pdu::getOptionalParameters() const { return m_vOptionalTlvParameters; }

bool Pdu::hasOptionalParameter(uint16_t nTag) const {
  auto iterTlv = std::find_if(m_vOptionalTlvParameters.begin(), m_vOptionalTlvParameters.end(),
                              [nTag](Tlv tlv) { return tlv.getTag() == nTag; });
  return iterTlv != m_vOptionalTlvParameters.end();
}

SubmitSm* Pdu::asSubmitSm() {
  if (m_nCommandId != constants::CMD_ID_SUBMIT_SM) {
    return nullptr;
  }

  return static_cast<SubmitSm*>(this);
}

DeliverSm* Pdu::asDeliverSm() {
  if (m_nCommandId != constants::CMD_ID_DELIVER_SM) {
    return nullptr;
  }

  return static_cast<DeliverSm*>(this);
}

BindTransmitterResp* Pdu::asBindTransmitterResp() {
  if (m_nCommandId != constants::CMD_ID_BIND_TRANSMITTER_RESP) {
    return nullptr;
  }

  return static_cast<BindTransmitterResp*>(this);
}

bool Pdu::equals(const Pdu& other) const {
  auto tlvComparator = [](const Tlv& lhs, const Tlv& rhs) { return lhs == rhs; };
  return m_nCommandLength == other.m_nCommandLength && m_nCommandId == other.m_nCommandId &&
         m_nCommandStatus == other.m_nCommandStatus &&
         m_nSequenceNumber == other.m_nSequenceNumber &&
         std::equal(m_vOptionalTlvParameters.begin(), m_vOptionalTlvParameters.end(),
                    other.m_vOptionalTlvParameters.begin(), tlvComparator);
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
  INFO << "Pdu::serializeOptionalParameters()";
  for (const auto& tlv : m_vOptionalTlvParameters) {
    tlv.serialize(os);
  }
}

void Pdu::deserializeOptionalParameters(std::istream& is) {
  INFO << "Pdu::deserializeOptionalParameters()";
  while (is.peek() != EOF) {
    Tlv tlv;
    tlv.deserialize(is);
    m_vOptionalTlvParameters.push_back(tlv);
  }
}

Pdu::UPtr Pdu::deserialize(std::istream& is) {
  INFO << "Pdu::deserialize()";

  // 1. Deserialize all 4 PDU header fields
  const uint32_t nCommandLength = binary::deserializeInt32(is);
  if (!util::isCommandLengthValid(nCommandLength)) {
    std::stringstream error;
    error << "Invalid command length detected during Pdu deserialization - [" << nCommandLength
          << "]";
    throw InvalidCommandLengthException(error.str());
  }

  INFO << "command length: [" << nCommandLength << "]";

  const uint32_t nCommandId = binary::deserializeInt32(is);
  if (!util::isCommandIdValid(nCommandId)) {
    std::stringstream error;
    error << "Invalid command id parsed detected Pdu deserialization - [" << nCommandId << "]";
    throw InvalidCommandIdException(error.str());
  }

  INFO << "command id: [" << util::commandIdToString(nCommandId) << "]";

  // TODO SG validate
  const uint32_t nCommandStatus = binary::deserializeInt32(is);
  INFO << "command status: [" << nCommandStatus << "]";

  const uint32_t nSequenceNumber = binary::deserializeInt32(is);
  INFO << "sequence number: [" << nSequenceNumber << "]";

  // 2. Deserialize PDU body
  auto deserializedPdu = getCommandIdToFactoryMap().at(nCommandId)(is);

  // 3. Set header fields
  deserializedPdu->m_nCommandLength = nCommandLength;
  deserializedPdu->m_nCommandStatus = nCommandStatus;
  deserializedPdu->m_nSequenceNumber = nSequenceNumber;

  return deserializedPdu;
}

}  // namespace smpp
