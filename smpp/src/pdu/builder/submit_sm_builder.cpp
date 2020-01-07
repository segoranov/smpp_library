#include "pdu/builder/submit_sm_builder.h"

namespace smpp::builder {

SubmitSmBuilder& SubmitSmBuilder::withCommandLength(uint32_t nCommandLength) {
  m_optCommandLength = nCommandLength;
  return *this;
}

SubmitSmBuilder& SubmitSmBuilder::withCommandStatus(uint32_t nCommandStatus) {
  m_optCommandStatus = nCommandStatus;
  return *this;
}
SubmitSmBuilder& SubmitSmBuilder::withSequenceNumber(uint32_t nSequenceNumber) {
  m_optSequenceNumber = nSequenceNumber;
  return *this;
}

SubmitSmBuilder& SubmitSmBuilder::withServiceType(const std::string& strServiceType) {
  m_optServiceType = strServiceType;
  return *this;
}

SubmitSmBuilder& SubmitSmBuilder::withSourceAddrTon(uint8_t nSourceAddrTon) {
  m_optSourceAddrTon = nSourceAddrTon;
  return *this;
}

SubmitSmBuilder& SubmitSmBuilder::withSourceAddrNpi(uint8_t nSourceAddrNpi) {
  m_optSourceAddrNpi = nSourceAddrNpi;
  return *this;
}

SubmitSmBuilder& SubmitSmBuilder::withSourceAddr(const std::string& strSourceAddr) {
  m_optSourceAddr = strSourceAddr;
  return *this;
}

SubmitSmBuilder& SubmitSmBuilder::withDestAddrTon(uint8_t nDestAddrTon) {
  m_optDestAddrTon = nDestAddrTon;
  return *this;
}

SubmitSmBuilder& SubmitSmBuilder::withDestAddrNpi(uint8_t nDestAddrNpi) {
  m_optDestAddrNpi = nDestAddrNpi;
  return *this;
}

SubmitSmBuilder& SubmitSmBuilder::withDestinationAddr(const std::string& strDestinationAddr) {
  m_optDestinationAddr = strDestinationAddr;
  return *this;
}

SubmitSmBuilder& SubmitSmBuilder::withEsmClass(uint8_t nEsmClass) {
  m_optEsmClass = nEsmClass;
  return *this;
}

SubmitSmBuilder& SubmitSmBuilder::withProtocolId(uint8_t nProtocolId) {
  m_optProtocolId = nProtocolId;
  return *this;
}

SubmitSmBuilder& SubmitSmBuilder::withPriorityFlag(uint8_t nPriorityFlag) {
  m_optPriorityFlag = nPriorityFlag;
  return *this;
}

SubmitSmBuilder& SubmitSmBuilder::withScheduleDeliveryTime(
    const std::string& strScheduleDeliveryTime) {
  m_optScheduleDeliveryTime = strScheduleDeliveryTime;
  return *this;
}

SubmitSmBuilder& SubmitSmBuilder::withValidityPeriod(const std::string& strValidityPeriod) {
  m_optValidityPeriod = strValidityPeriod;
  return *this;
}

SubmitSmBuilder& SubmitSmBuilder::withRegisteredDelivery(uint8_t nRegisteredDelivery) {
  m_optRegisteredDelivery = nRegisteredDelivery;
  return *this;
}

SubmitSmBuilder& SubmitSmBuilder::withReplaceIfPresentFlag(uint8_t nReplaceIfPresentFlag) {
  m_optReplaceIfPresentFlag = nReplaceIfPresentFlag;
  return *this;
}

SubmitSmBuilder& SubmitSmBuilder::withDataCoding(uint8_t nDataCoding) {
  m_optDataCoding = nDataCoding;
  return *this;
}

SubmitSmBuilder& SubmitSmBuilder::withSmDefaultMsgId(uint8_t nSmDefaultMsgId) {
  m_optSmDefaultMsgId = nSmDefaultMsgId;
  return *this;
}

SubmitSmBuilder& SubmitSmBuilder::withSmLength(uint8_t nSmLength) {
  m_optSmLength = nSmLength;
  return *this;
}

SubmitSmBuilder& SubmitSmBuilder::withShortMessage(const std::string& strShortMessage) {
  m_optShortMessage = strShortMessage;
  return *this;
}

SubmitSmBuilder& SubmitSmBuilder::withOptionalParameters(const std::vector<Tlv>& tlvs) {
  m_vOptionalTlvParameters = tlvs;
  return *this;
}

}  // namespace smpp::builder