#ifndef PDU_H
#define PDU_H

#include <optional>
#include <string>

#include "../smppconstants.h"
#include "../tlv/tlv.h"

namespace smpp {

struct PduHeader {
  uint32_t m_nCommandLength;
  uint32_t m_nCommandID;
  uint32_t m_nCommandStatus;
  uint32_t m_nSequenceNumber;

  PduHeader(uint32_t nCommandLength = 0, uint32_t nCommandID = 0, uint32_t nCommandStatus = 0,
            uint32_t nSequenceNumber = 0);
};

class Pdu {
 private:
  PduHeader m_pduHeader;
  std::vector<Tlv> m_vOptionalTlvParameters;

 private:
  const bool m_bIsRequest;

 public:
  Pdu(const PduHeader& pduHeader, bool isRequest);

  uint32_t getCommandLength() const { return m_pduHeader.m_nCommandLength; }
  uint32_t getCommandId() const { return m_pduHeader.m_nCommandID; }
  uint32_t getCommandStatus() const { return m_pduHeader.m_nCommandStatus; }
  uint32_t getSequenceNumber() const { return m_pduHeader.m_nSequenceNumber; }
  std::vector<Tlv> getOptionalParameters() const { return m_vOptionalTlvParameters; }

  void addOptionalParameter(const Tlv& tlv);

  /**
   * Removes an optional parameter by tag.  Will only remove the first matching tag.
   * @param nTag That tag to remove
   * @return Empty optional if no TLV removed, or the TLV removed.
   */
  std::optional<Tlv> removeOptionalParameter(uint16_t nTag);

  bool hasOptionalParameter(uint16_t nTag) const;

  bool isRequest() const { return m_bIsRequest; }
  bool isResponse() const { return !m_bIsRequest; }
};



}  // namespace smpp

#endif