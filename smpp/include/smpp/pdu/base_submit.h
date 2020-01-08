#ifndef BASE_SUBMIT_H
#define BASE_SUBMIT_H

#include <string>

#include "smpp/pdu/pdu_request.h"

namespace smpp {

class BaseSubmit : public PduRequest {
 protected:
  std::string m_strServiceType;
  uint8_t m_nSourceAddrTon;
  uint8_t m_nSourceAddrNpi;
  std::string m_strSourceAddr;

  uint8_t m_nEsmClass;
  uint8_t m_nProtocolId;
  uint8_t m_nPriorityFlag;
  std::string m_strScheduleDeliveryTime;
  std::string m_strValidityPeriod;
  uint8_t m_nRegisteredDelivery;
  uint8_t m_nReplaceIfPresentFlag;
  uint8_t m_nDataCoding;
  uint8_t m_nSmDefaultMsgId;
  uint8_t m_nSmLength;
  std::string m_strShortMessage;

 public:
  explicit BaseSubmit(uint32_t nCommandId);

  std::string getServiceType() const;
  uint8_t getSourceAddrTon() const;
  uint8_t getSourceAddrNpi() const;
  std::string getSourceAddr() const;
  uint8_t getEsmClass() const;
  uint8_t getProtocolId() const;
  std::string getScheduleDeliveryTime() const;
  std::string getValidityPeriod() const;
  uint8_t getRegisteredDelivery() const;
  uint8_t getReplaceIfPresentFlag() const;
  uint8_t getDataCoding() const;
  uint8_t getSmDefaultMsgId() const;
  uint8_t getSmLength() const;
  std::string getShortMessage() const;
};

}  // namespace smpp

#endif