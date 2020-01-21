#include "smpp/pdu/builder/submit_multi_builder.h"

namespace smpp::builder {

SubmitMultiBuilder& SubmitMultiBuilder::withCommandStatus(uint32_t nCommandStatus) {
  m_optCommandStatus = nCommandStatus;
  return *this;
}
SubmitMultiBuilder& SubmitMultiBuilder::withSequenceNumber(uint32_t nSequenceNumber) {
  m_optSequenceNumber = nSequenceNumber;
  return *this;
}

SubmitMultiBuilder& SubmitMultiBuilder::withServiceType(const std::string& strServiceType) {
  m_optServiceType = strServiceType;
  return *this;
}

SubmitMultiBuilder& SubmitMultiBuilder::withSourceAddrTon(uint8_t nSourceAddrTon) {
  m_optSourceAddrTon = nSourceAddrTon;
  return *this;
}

SubmitMultiBuilder& SubmitMultiBuilder::withSourceAddrNpi(uint8_t nSourceAddrNpi) {
  m_optSourceAddrNpi = nSourceAddrNpi;
  return *this;
}

SubmitMultiBuilder& SubmitMultiBuilder::withSourceAddr(const std::string& strSourceAddr) {
  m_optSourceAddr = strSourceAddr;
  return *this;
}

SubmitMultiBuilder& SubmitMultiBuilder::withDestinationAddresses(
    const smpp::SubmitMultiDestinationAddresses& destinationAddresses) {
  m_optDestinationAddresses = destinationAddresses;
  return *this;
}

SubmitMultiBuilder& SubmitMultiBuilder::withEsmClass(uint8_t nEsmClass) {
  m_optEsmClass = nEsmClass;
  return *this;
}

SubmitMultiBuilder& SubmitMultiBuilder::withProtocolId(uint8_t nProtocolId) {
  m_optProtocolId = nProtocolId;
  return *this;
}

SubmitMultiBuilder& SubmitMultiBuilder::withPriorityFlag(uint8_t nPriorityFlag) {
  m_optPriorityFlag = nPriorityFlag;
  return *this;
}

SubmitMultiBuilder& SubmitMultiBuilder::withScheduleDeliveryTime(
    const std::string& strScheduleDeliveryTime) {
  m_optScheduleDeliveryTime = strScheduleDeliveryTime;
  return *this;
}

SubmitMultiBuilder& SubmitMultiBuilder::withValidityPeriod(const std::string& strValidityPeriod) {
  m_optValidityPeriod = strValidityPeriod;
  return *this;
}

SubmitMultiBuilder& SubmitMultiBuilder::withRegisteredDelivery(uint8_t nRegisteredDelivery) {
  m_optRegisteredDelivery = nRegisteredDelivery;
  return *this;
}

SubmitMultiBuilder& SubmitMultiBuilder::withReplaceIfPresentFlag(uint8_t nReplaceIfPresentFlag) {
  m_optReplaceIfPresentFlag = nReplaceIfPresentFlag;
  return *this;
}

SubmitMultiBuilder& SubmitMultiBuilder::withDataCoding(uint8_t nDataCoding) {
  m_optDataCoding = nDataCoding;
  return *this;
}

SubmitMultiBuilder& SubmitMultiBuilder::withSmDefaultMsgId(uint8_t nSmDefaultMsgId) {
  m_optSmDefaultMsgId = nSmDefaultMsgId;
  return *this;
}

SubmitMultiBuilder& SubmitMultiBuilder::withSmLength(uint8_t nSmLength) {
  m_optSmLength = nSmLength;
  return *this;
}

SubmitMultiBuilder& SubmitMultiBuilder::withShortMessage(const std::string& strShortMessage) {
  m_optShortMessage = strShortMessage;
  return *this;
}

SubmitMultiBuilder& SubmitMultiBuilder::withOptionalParameters(const std::vector<Tlv>& tlvs) {
  m_vOptionalTlvParameters = tlvs;
  return *this;
}

}  // namespace smpp::builder