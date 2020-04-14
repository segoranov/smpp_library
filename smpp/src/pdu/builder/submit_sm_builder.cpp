#include "smpp/pdu/builder/submit_sm_builder.h"

namespace smpp::builder {

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

SubmitSmBuilder& SubmitSmBuilder::withShortMessage(const std::string& strShortMessage) {
  m_optShortMessage = strShortMessage;
  return *this;
}

SubmitSmBuilder& SubmitSmBuilder::withOptionalParameters(const std::vector<Tlv>& tlvs) {
  m_vOptionalTlvParameters = tlvs;
  return *this;
}

void SubmitSmBuilder::checkAllValuesArePresent() const {
  if (!m_optSequenceNumber.has_value()) {
    throw UndefinedValueException("SubmitSmBuilder: Undefined sequence number");
  }

  if (!m_optServiceType.has_value()) {
    throw UndefinedValueException("SubmitSmBuilder: Undefined service type");
  }

  if (!m_optSourceAddrTon.has_value()) {
    throw UndefinedValueException("SubmitSmBuilder: Undefined source addr ton");
  }

  if (!m_optSourceAddrNpi.has_value()) {
    throw UndefinedValueException("SubmitSmBuilder: Undefined source addr npi");
  }

  if (!m_optSourceAddr.has_value()) {
    throw UndefinedValueException("SubmitSmBuilder: Undefined source addr");
  }

  if (!m_optDestAddrTon.has_value()) {
    throw UndefinedValueException("SubmitSmBuilder: Undefined dest addr ton");
  }

  if (!m_optDestAddrNpi.has_value()) {
    throw UndefinedValueException("SubmitSmBuilder: Undefined dest addr npi");
  }

  if (!m_optDestinationAddr.has_value()) {
    throw UndefinedValueException("SubmitSmBuilder: Undefined destination addr");
  }

  if (!m_optEsmClass.has_value()) {
    throw UndefinedValueException("SubmitSmBuilder: Undefined esm class");
  }

  if (!m_optProtocolId.has_value()) {
    throw UndefinedValueException("SubmitSmBuilder: Undefined protocol id");
  }

  if (!m_optPriorityFlag.has_value()) {
    throw UndefinedValueException("SubmitSmBuilder: Undefined priority flag");
  }

  if (!m_optScheduleDeliveryTime.has_value()) {
    throw UndefinedValueException("SubmitSmBuilder: Undefined schedule delivery time");
  }

  if (!m_optValidityPeriod.has_value()) {
    throw UndefinedValueException("SubmitSmBuilder: Undefined validity period");
  }

  if (!m_optRegisteredDelivery.has_value()) {
    throw UndefinedValueException("SubmitSmBuilder: Undefined registered delivery");
  }

  if (!m_optReplaceIfPresentFlag.has_value()) {
    throw UndefinedValueException("SubmitSmBuilder: Undefined replace if present flag");
  }

  if (!m_optDataCoding.has_value()) {
    throw UndefinedValueException("SubmitSmBuilder: Undefined data coding");
  }

  if (!m_optSmDefaultMsgId.has_value()) {
    throw UndefinedValueException("SubmitSmBuilder: Undefined sm default msg id");
  }

  if (!m_optShortMessage.has_value()) {
    throw UndefinedValueException("SubmitSmBuilder: Undefined short message");
  }
}

}  // namespace smpp::builder