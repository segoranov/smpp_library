#include "smpp/pdu/submit_sm.h"

#include "smpp/pdu/builder/submit_sm_builder.h"
#include "smpp/util/logging.h"
#include "smpp/util/serialization_util.h"

namespace smpp {

SubmitSm::SubmitSm() : BaseSubmit{constants::CMD_ID_SUBMIT_SM} {}

SubmitSm::SubmitSm(const builder::SubmitSmBuilder& params)
    : BaseSubmit{constants::CMD_ID_SUBMIT_SM} {
  if (!params.m_optCommandStatus.has_value()) {
    throw UndefinedValueException("SubmitSm(): Undefined command status");
  }

  if (!params.m_optSequenceNumber.has_value()) {
    throw UndefinedValueException("SubmitSm(): Undefined sequence number");
  }

  if (!params.m_optServiceType.has_value()) {
    throw UndefinedValueException("SubmitSm(): Undefined service type");
  }

  if (!params.m_optSourceAddrTon.has_value()) {
    throw UndefinedValueException("SubmitSm(): Undefined source addr ton");
  }

  if (!params.m_optSourceAddrNpi.has_value()) {
    throw UndefinedValueException("SubmitSm(): Undefined source addr npi");
  }

  if (!params.m_optSourceAddr.has_value()) {
    throw UndefinedValueException("SubmitSm(): Undefined source addr");
  }

  if (!params.m_optDestAddrTon.has_value()) {
    throw UndefinedValueException("SubmitSm(): Undefined dest addr ton");
  }

  if (!params.m_optDestAddrNpi.has_value()) {
    throw UndefinedValueException("SubmitSm(): Undefined dest addr npi");
  }

  if (!params.m_optDestinationAddr.has_value()) {
    throw UndefinedValueException("SubmitSm(): Undefined destination addr");
  }

  if (!params.m_optEsmClass.has_value()) {
    throw UndefinedValueException("SubmitSm(): Undefined esm class");
  }

  if (!params.m_optProtocolId.has_value()) {
    throw UndefinedValueException("SubmitSm(): Undefined protocol id");
  }

  if (!params.m_optPriorityFlag.has_value()) {
    throw UndefinedValueException("SubmitSm(): Undefined priority flag");
  }

  if (!params.m_optScheduleDeliveryTime.has_value()) {
    throw UndefinedValueException("SubmitSm(): Undefined schedule delivery time");
  }

  if (!params.m_optValidityPeriod.has_value()) {
    throw UndefinedValueException("SubmitSm(): Undefined validity period");
  }

  if (!params.m_optRegisteredDelivery.has_value()) {
    throw UndefinedValueException("SubmitSm(): Undefined registered delivery");
  }

  if (!params.m_optReplaceIfPresentFlag.has_value()) {
    throw UndefinedValueException("SubmitSm(): Undefined replace if present flag");
  }

  if (!params.m_optDataCoding.has_value()) {
    throw UndefinedValueException("SubmitSm(): Undefined data coding");
  }

  if (!params.m_optSmDefaultMsgId.has_value()) {
    throw UndefinedValueException("SubmitSm(): Undefined sm default msg id");
  }

  if (!params.m_optShortMessage.has_value()) {
    throw UndefinedValueException("SubmitSm(): Undefined short message");
  }

  m_nCommandStatus = params.m_optCommandStatus.value();
  m_nSequenceNumber = params.m_optSequenceNumber.value();
  m_strServiceType = params.m_optServiceType.value();
  m_nSourceAddrTon = params.m_optSourceAddrTon.value();
  m_nSourceAddrNpi = params.m_optSourceAddrNpi.value();
  m_strSourceAddr = params.m_optSourceAddr.value();
  m_nDestAddrTon = params.m_optDestAddrTon.value();
  m_nDestAddrNpi = params.m_optDestAddrNpi.value();
  m_strDestinationAddr = params.m_optDestinationAddr.value();
  m_nEsmClass = params.m_optEsmClass.value();
  m_nProtocolId = params.m_optProtocolId.value();
  m_strScheduleDeliveryTime = params.m_optScheduleDeliveryTime.value();
  m_strValidityPeriod = params.m_optValidityPeriod.value();
  m_nRegisteredDelivery = params.m_optRegisteredDelivery.value();
  m_nReplaceIfPresentFlag = params.m_optReplaceIfPresentFlag.value();
  m_nDataCoding = params.m_optDataCoding.value();
  m_nSmDefaultMsgId = params.m_optSmDefaultMsgId.value();
  m_nSmLength = params.m_optShortMessage.value().size();
  m_strShortMessage = params.m_optShortMessage.value();
  m_vOptionalTlvParameters = params.m_vOptionalTlvParameters;

  // Add PDU header to command length
  m_nCommandLength = smpp::constants::PDU_HEADER_LENGTH;

  // Add C-octet strings to command length without forgetting to add 1
  // for the null terminating character
  m_nCommandLength += m_strServiceType.size() + 1;
  m_nCommandLength += m_strSourceAddr.size() + 1;
  m_nCommandLength += m_strDestinationAddr.size() + 1;
  m_nCommandLength += m_strScheduleDeliveryTime.size() + 1;
  m_nCommandLength += m_strValidityPeriod.size() + 1;
  m_nCommandLength += m_strShortMessage.size() + 1;

  // 11 more mandatory fields with size 1 byte
  m_nCommandLength += 11;

  // Add optional parameters size to command length
  for (const auto& tlv : m_vOptionalTlvParameters) {
    m_nCommandLength += tlv.size();
  }
}

uint8_t SubmitSm::getDestAddrTon() const { return m_nDestAddrTon; }

uint8_t SubmitSm::getDestAddrNpi() const { return m_nDestAddrNpi; }

std::string SubmitSm::getDestinationAddr() const { return m_strDestinationAddr; }

void SubmitSm::serialize(std::ostream& os) const {
  INFO << "SubmitSm::serialize()";
  serializeHeader(os);
  binary::serializeNullTerminatedString(m_strServiceType, os);
  binary::serializeInt8(m_nSourceAddrTon, os);
  binary::serializeInt8(m_nSourceAddrNpi, os);
  binary::serializeNullTerminatedString(m_strSourceAddr, os);
  binary::serializeInt8(m_nDestAddrTon, os);
  binary::serializeInt8(m_nDestAddrNpi, os);
  binary::serializeNullTerminatedString(m_strDestinationAddr, os);
  binary::serializeInt8(m_nEsmClass, os);
  binary::serializeInt8(m_nProtocolId, os);
  binary::serializeInt8(m_nPriorityFlag, os);
  binary::serializeNullTerminatedString(m_strScheduleDeliveryTime, os);
  binary::serializeNullTerminatedString(m_strValidityPeriod, os);
  binary::serializeInt8(m_nRegisteredDelivery, os);
  binary::serializeInt8(m_nReplaceIfPresentFlag, os);
  binary::serializeInt8(m_nDataCoding, os);
  binary::serializeInt8(m_nSmDefaultMsgId, os);
  binary::serializeInt8(m_nSmLength, os);
  binary::serializeOctetString(m_strShortMessage, os);
  serializeOptionalParameters(os);  // optional parameters are part of the body
}

std::unique_ptr<SubmitSm> SubmitSm::create(std::istream& is) {
  INFO << "SubmitSm::create()";

  auto submitSmPtr = std::unique_ptr<SubmitSm>{new SubmitSm{}};

  const std::string strServiceType = binary::deserializeNullTerminatedString(is);
  submitSmPtr->m_strServiceType = strServiceType;
  DEBUG << "SubmitSm::create() strServiceType = [" << strServiceType << "]";

  const uint8_t nSourceAddrTon = binary::deserializeInt8(is);
  submitSmPtr->m_nSourceAddrTon = nSourceAddrTon;
  DEBUG << "SubmitSm::create() nSourceAddrTon = [" << nSourceAddrTon << "]";

  const uint8_t nSourceAddrNpi = binary::deserializeInt8(is);
  submitSmPtr->m_nSourceAddrNpi = nSourceAddrNpi;
  DEBUG << "SubmitSm::create() nSourceAddrTon = [" << nSourceAddrTon << "]";

  const std::string strSourceAddr = binary::deserializeNullTerminatedString(is);
  submitSmPtr->m_strSourceAddr = strSourceAddr;
  DEBUG << "SubmitSm::create() nSourceAddrTon = [" << nSourceAddrTon << "]";

  const uint8_t nDestAddrTon = binary::deserializeInt8(is);
  submitSmPtr->m_nDestAddrTon = nDestAddrTon;
  DEBUG << "SubmitSm::create() nDestAddrTon = [" << nDestAddrTon << "]";

  const uint8_t nDestAddrNpi = binary::deserializeInt8(is);
  submitSmPtr->m_nDestAddrNpi = nDestAddrNpi;
  DEBUG << "SubmitSm::create() nDestAddrNpi = [" << nDestAddrNpi << "]";

  const std::string strDestinationAddr = binary::deserializeNullTerminatedString(is);
  submitSmPtr->m_strDestinationAddr = strDestinationAddr;
  DEBUG << "SubmitSm::create() strDestinationAddr = [" << strDestinationAddr << "]";

  const uint8_t nEsmClass = binary::deserializeInt8(is);
  submitSmPtr->m_nEsmClass = nEsmClass;
  DEBUG << "SubmitSm::create() nEsmClass = [" << nEsmClass << "]";

  const uint8_t nProtocolId = binary::deserializeInt8(is);
  submitSmPtr->m_nProtocolId = nProtocolId;
  DEBUG << "SubmitSm::create() nProtocolId = [" << nProtocolId << "]";

  const uint8_t nPriorityFlag = binary::deserializeInt8(is);
  submitSmPtr->m_nPriorityFlag = nPriorityFlag;
  DEBUG << "SubmitSm::create() nPriorityFlag = [" << nPriorityFlag << "]";

  const std::string strScheduleDeliveryTime = binary::deserializeNullTerminatedString(is);
  submitSmPtr->m_strScheduleDeliveryTime = strScheduleDeliveryTime;
  DEBUG << "SubmitSm::create() strScheduleDeliveryTime = [" << strScheduleDeliveryTime << "]";

  const std::string strValidityPeriod = binary::deserializeNullTerminatedString(is);
  submitSmPtr->m_strValidityPeriod = strValidityPeriod;
  DEBUG << "SubmitSm::create() strValidityPeriod = [" << strValidityPeriod << "]";

  const uint8_t nRegisteredDelivery = binary::deserializeInt8(is);
  submitSmPtr->m_nRegisteredDelivery = nRegisteredDelivery;
  DEBUG << "SubmitSm::create() nRegisteredDelivery = [" << nRegisteredDelivery << "]";

  const uint8_t nReplaceIfPresentFlag = binary::deserializeInt8(is);
  submitSmPtr->m_nReplaceIfPresentFlag = nReplaceIfPresentFlag;
  DEBUG << "SubmitSm::create() nReplaceIfPresentFlag = [" << nReplaceIfPresentFlag << "]";

  const uint8_t nDataCoding = binary::deserializeInt8(is);
  submitSmPtr->m_nDataCoding = nDataCoding;
  DEBUG << "SubmitSm::create() nDataCoding = [" << nDataCoding << "]";

  const uint8_t nSmDefaultMsgId = binary::deserializeInt8(is);
  submitSmPtr->m_nSmDefaultMsgId = nSmDefaultMsgId;
  DEBUG << "SubmitSm::create() nSmDefaultMsgId = [" << nSmDefaultMsgId << "]";

  const uint8_t nSmLength = binary::deserializeInt8(is);
  submitSmPtr->m_nSmLength = nSmLength;
  DEBUG << "SubmitSm::create() nSmLength = [" << nSmLength << "]";

  const std::string strShortMessage = binary::deserializeOctetString(nSmLength, is);
  submitSmPtr->m_strShortMessage = strShortMessage;
  DEBUG << "SubmitSm::create() strShortMessage = [" << strShortMessage << "]";

  submitSmPtr->deserializeOptionalParameters(is);

  return submitSmPtr;
}

}  // namespace smpp