#ifndef PDU_H
#define PDU_H

#include <arpa/inet.h>

#include <cereal/access.hpp>
#include <memory>
#include <optional>
#include <string>

#include "smppconstants.h"
#include "tlv/tlv.h"

namespace smpp {

class Buffer;

class Pdu {
  friend class DefaultPduTranscoder;

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
};

template <typename Archive>
void Pdu::save(Archive& archive) const {
  archive(htonl(m_nCommandLength), htonl(m_nCommandId), htonl(m_nCommandStatus),
          htonl(m_nSequenceNumber));
}

template <class Archive>
void Pdu::load(Archive& archive) {
  auto readToHostByteOrder = [&archive](uint32_t& value) {
    uint32_t temp;
    archive(temp);
    value = ntohl(temp);
  };

  readToHostByteOrder(m_nCommandLength);
  readToHostByteOrder(m_nCommandId);
  readToHostByteOrder(m_nCommandStatus);
  readToHostByteOrder(m_nSequenceNumber);
}

}  // namespace smpp

#endif