#ifndef PDU_H
#define PDU_H

#include <arpa/inet.h>

#include <cereal/access.hpp>
#include <memory>
#include <optional>
#include <sstream>
#include <string>

#include "smppconstants.h"
#include "smppexceptions.h"
#include "tlv/tlv.h"
#include "util/smpp_util.h"

namespace smpp {

class Buffer;

class Pdu {
 private:
  // PDU Header
  uint32_t m_nCommandLength;
  uint32_t m_nCommandId;
  uint32_t m_nCommandStatus;
  uint32_t m_nSequenceNumber;

  std::vector<Tlv> m_vOptionalTlvParameters;

 private:
  const bool m_bIsRequest;

 public:
  explicit Pdu(uint32_t nCommandId, bool bIsRequest);

  uint32_t getCommandLength() const;
  uint32_t getCommandId() const;
  uint32_t getCommandStatus() const;
  uint32_t getSequenceNumber() const;
  std::vector<Tlv> getOptionalParameters() const;

  void setCommandLength(uint32_t nCommandLength);
  void setCommandStatus(uint32_t nCommandStatus);
  void setSequenceNumber(uint32_t nSequenceNumber);

  void addOptionalParameter(const Tlv& tlv);

  /**
   * Removes an optional parameter by tag.  Will only remove the first matching tag.
   * @param nTag That tag to remove
   * @return Empty optional if no TLV removed, or the TLV removed.
   */
  std::optional<Tlv> removeOptionalParameter(uint16_t nTag);

  bool hasOptionalParameter(uint16_t nTag) const;

  bool isRequest() const;
  bool isResponse() const;

 private:
  /**
   * Serialization/Deserialization
   */

  friend class cereal::access;

  template <typename Archive>
  void save(Archive& archive) const;

  template <class Archive>
  void load(Archive& archive);

  /**
   * Helper methods
   */

  template <typename Archive>
  void deserializeCommandLength(Archive& archive);

  template <typename Archive>
  void deserializeCommandId(Archive& archive);

  template <typename Archive>
  void deserializeCommandStatus(Archive& archive);

  template <typename Archive>
  void deserializeSequenceNumber(Archive& archive);
};

template <typename Archive>
void Pdu::save(Archive& archive) const {
  if (!util::isCommandLengthValid(m_nCommandLength)) {
    std::stringstream error;
    error << "Invalid command length parsed during serialization - [" << m_nCommandLength << "]";
    throw InvalidCommandLengthException(error.str());
  }

  if (!util::isCommandIdValid(m_nCommandId)) {
    std::stringstream error;
    error << "Invalid command id parsed during serialization - [" << m_nCommandId << "]";
    throw InvalidCommandIdException(error.str());
  }

  // TODO SG: validate command status and sequence number

  archive(htonl(m_nCommandLength), htonl(m_nCommandId), htonl(m_nCommandStatus),
          htonl(m_nSequenceNumber));
}

template <class Archive>
void Pdu::load(Archive& archive) {
  deserializeCommandLength(archive);
  deserializeCommandId(archive);
  deserializeCommandStatus(archive);
  deserializeSequenceNumber(archive);
}

template <typename Archive>
void Pdu::deserializeCommandLength(Archive& archive) {
  uint32_t nCommandLength;
  archive(nCommandLength);
  nCommandLength = ntohl(nCommandLength);

  if (!util::isCommandLengthValid(nCommandLength)) {
    std::stringstream error;
    error << "Invalid command length parsed during deserialization - [" << nCommandLength << "]";
    throw InvalidCommandLengthException(error.str());
  }

  // command length is valid; set it accordingly
  m_nCommandLength = nCommandLength;
}

template <typename Archive>
void Pdu::deserializeCommandId(Archive& archive) {
  uint32_t nCommandId;
  archive(nCommandId);
  nCommandId = ntohl(nCommandId);

  if (!util::isCommandIdValid(nCommandId)) {
    std::stringstream error;
    error << "Invalid command id parsed - [" << nCommandId << "]";
    throw InvalidCommandIdException(error.str());
  }

  // command id is valid; set it accordingly
  m_nCommandId = nCommandId;
}

template <typename Archive>
void Pdu::deserializeCommandStatus(Archive& archive) {
  uint32_t nCommandStatus;
  archive(nCommandStatus);
  nCommandStatus = ntohl(nCommandStatus);

  // TODO SG: validation?

  // command status is valid; set it accordingly
  m_nCommandStatus = nCommandStatus;
}

template <typename Archive>
void Pdu::deserializeSequenceNumber(Archive& archive) {
  uint32_t nSequenceNumber;
  archive(nSequenceNumber);
  nSequenceNumber = ntohl(nSequenceNumber);

  // TODO SG: validation?

  // sequence number is valid; set it accordingly
  m_nSequenceNumber = nSequenceNumber;
}

}  // namespace smpp

#endif