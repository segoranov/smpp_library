#ifndef PDU_H
#define PDU_H

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

  /**
   * Constructs a PDU by command id
   *
   * @throws InvalidCommandIdException if the command ID is invalid
   * @return the newly created PDU
   */
  static std::unique_ptr<Pdu> createPduByCommandId(uint32_t nCommandId);

 protected:
  /**
   * Read and write PDU body
   */
  virtual void readBody(Buffer& buffer) = 0;
  virtual void writeBody(Buffer& buffer) const = 0;

  /**
   * Read and write PDU optional parameters - TLVs
   */
  void readOptionalParameters(Buffer& buffer);
  void writeOptionalParameters(Buffer& buffer) const;
};

}  // namespace smpp

#endif