#ifndef PDU_H
#define PDU_H

#include <string>

#include "../tlv/tlv.h"

namespace smpp {

class Pdu {
 private:
  uint32_t m_nCommandLength;
  uint32_t m_nCommandID;
  uint32_t m_nCommandStatus;
  uint32_t m_nSequenceNumber;

  std::vector<TLV> m_vOptionalTLVParameters;

  std::string m_strBuffer;

 public:
  Pdu(uint32_t nCommandLength = 0, uint32_t nCommandID = 0, uint32_t nCommandStatus = 0,
      uint32_t nSequenceNumber = 0);

  /**
   * @return PDU size in octets.
   */
  int getSize();

  uint32_t getCommandLength() const { return m_nCommandLength; }
  uint32_t getCommandId() const { return m_nCommandID; }
  uint32_t getCommandStatus() const { return m_nCommandStatus; }
  uint32_t getSequenceNumber() const { return m_nSequenceNumber; }
  std::vector<TLV> getOptionalParameters() const { return m_vOptionalTLVParameters; }
};

}  // namespace smpp

#endif