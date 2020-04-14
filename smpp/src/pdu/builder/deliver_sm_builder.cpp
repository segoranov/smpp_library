#include "smpp/pdu/builder/deliver_sm_builder.h"

namespace smpp::builder {

DeliverSmBuilder& DeliverSmBuilder::withSequenceNumber(uint32_t nSequenceNumber) {
  m_optSequenceNumber = nSequenceNumber;
  return *this;
}

DeliverSmBuilder& DeliverSmBuilder::withServiceType(const std::string& strServiceType) {
  m_optServiceType = strServiceType;
  return *this;
}

DeliverSmBuilder& DeliverSmBuilder::withSourceAddrTon(uint8_t nSourceAddrTon) {
  m_optSourceAddrTon = nSourceAddrTon;
  return *this;
}

DeliverSmBuilder& DeliverSmBuilder::withSourceAddrNpi(uint8_t nSourceAddrNpi) {
  m_optSourceAddrNpi = nSourceAddrNpi;
  return *this;
}

DeliverSmBuilder& DeliverSmBuilder::withSourceAddr(const std::string& strSourceAddr) {
  m_optSourceAddr = strSourceAddr;
  return *this;
}

DeliverSmBuilder& DeliverSmBuilder::withDestAddrTon(uint8_t nDestAddrTon) {
  m_optDestAddrTon = nDestAddrTon;
  return *this;
}

DeliverSmBuilder& DeliverSmBuilder::withDestAddrNpi(uint8_t nDestAddrNpi) {
  m_optDestAddrNpi = nDestAddrNpi;
  return *this;
}

DeliverSmBuilder& DeliverSmBuilder::withDestinationAddr(const std::string& strDestinationAddr) {
  m_optDestinationAddr = strDestinationAddr;
  return *this;
}

DeliverSmBuilder& DeliverSmBuilder::withEsmClass(uint8_t nEsmClass) {
  m_optEsmClass = nEsmClass;
  return *this;
}

DeliverSmBuilder& DeliverSmBuilder::withProtocolId(uint8_t nProtocolId) {
  m_optProtocolId = nProtocolId;
  return *this;
}

DeliverSmBuilder& DeliverSmBuilder::withPriorityFlag(uint8_t nPriorityFlag) {
  m_optPriorityFlag = nPriorityFlag;
  return *this;
}

DeliverSmBuilder& DeliverSmBuilder::withScheduleDeliveryTime(
    const std::string& strScheduleDeliveryTime) {
  m_optScheduleDeliveryTime = strScheduleDeliveryTime;
  return *this;
}

DeliverSmBuilder& DeliverSmBuilder::withValidityPeriod(const std::string& strValidityPeriod) {
  m_optValidityPeriod = strValidityPeriod;
  return *this;
}

DeliverSmBuilder& DeliverSmBuilder::withRegisteredDelivery(uint8_t nRegisteredDelivery) {
  m_optRegisteredDelivery = nRegisteredDelivery;
  return *this;
}

DeliverSmBuilder& DeliverSmBuilder::withReplaceIfPresentFlag(uint8_t nReplaceIfPresentFlag) {
  m_optReplaceIfPresentFlag = nReplaceIfPresentFlag;
  return *this;
}

DeliverSmBuilder& DeliverSmBuilder::withDataCoding(uint8_t nDataCoding) {
  m_optDataCoding = nDataCoding;
  return *this;
}

DeliverSmBuilder& DeliverSmBuilder::withSmDefaultMsgId(uint8_t nSmDefaultMsgId) {
  m_optSmDefaultMsgId = nSmDefaultMsgId;
  return *this;
}

DeliverSmBuilder& DeliverSmBuilder::withShortMessage(const std::string& strShortMessage) {
  m_optShortMessage = strShortMessage;
  return *this;
}

DeliverSmBuilder& DeliverSmBuilder::withOptionalParameters(const std::vector<Tlv>& tlvs) {
  m_vOptionalTlvParameters = tlvs;
  return *this;
}

void DeliverSmBuilder::checkAllValuesArePresent() const {
  if (!m_optSequenceNumber.has_value()) {
    throw UndefinedValueException("DeliverSmBuilder: Undefined sequence number");
  }

  if (!m_optServiceType.has_value()) {
    throw UndefinedValueException("DeliverSmBuilder: Undefined service type");
  }

  if (!m_optSourceAddrTon.has_value()) {
    throw UndefinedValueException("DeliverSmBuilder: Undefined source addr ton");
  }

  if (!m_optSourceAddrNpi.has_value()) {
    throw UndefinedValueException("DeliverSmBuilder: Undefined source addr npi");
  }

  if (!m_optSourceAddr.has_value()) {
    throw UndefinedValueException("DeliverSmBuilder: Undefined source addr");
  }

  if (!m_optDestAddrTon.has_value()) {
    throw UndefinedValueException("DeliverSmBuilder: Undefined dest addr ton");
  }

  if (!m_optDestAddrNpi.has_value()) {
    throw UndefinedValueException("DeliverSmBuilder: Undefined dest addr npi");
  }

  if (!m_optDestinationAddr.has_value()) {
    throw UndefinedValueException("DeliverSmBuilder: Undefined destination addr");
  }

  if (!m_optEsmClass.has_value()) {
    throw UndefinedValueException("DeliverSmBuilder: Undefined esm class");
  }

  if (!m_optProtocolId.has_value()) {
    throw UndefinedValueException("DeliverSmBuilder: Undefined protocol id");
  }

  if (!m_optPriorityFlag.has_value()) {
    throw UndefinedValueException("DeliverSmBuilder: Undefined priority flag");
  }

  if (!m_optScheduleDeliveryTime.has_value()) {
    throw UndefinedValueException("DeliverSmBuilder: Undefined schedule delivery time");
  }

  if (!m_optValidityPeriod.has_value()) {
    throw UndefinedValueException("DeliverSmBuilder: Undefined validity period");
  }

  if (!m_optRegisteredDelivery.has_value()) {
    throw UndefinedValueException("DeliverSmBuilder: Undefined registered delivery");
  }

  if (!m_optReplaceIfPresentFlag.has_value()) {
    throw UndefinedValueException("DeliverSmBuilder: Undefined replace if present flag");
  }

  if (!m_optDataCoding.has_value()) {
    throw UndefinedValueException("DeliverSmBuilder: Undefined data coding");
  }

  if (!m_optSmDefaultMsgId.has_value()) {
    throw UndefinedValueException("DeliverSmBuilder: Undefined sm default msg id");
  }

  if (!m_optShortMessage.has_value()) {
    throw UndefinedValueException("DeliverSmBuilder: Undefined short message");
  }
}

}  // namespace smpp::builder