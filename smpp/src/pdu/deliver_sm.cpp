#include "smpp/pdu/deliver_sm.h"

#include "smpp/pdu/builder/deliver_sm_builder.h"

#include "smpp/util/serialization_util.h"

namespace smpp {

DeliverSm::DeliverSm() : Pdu{constants::CMD_ID_DELIVER_SM} {}

DeliverSm::DeliverSm(const builder::DeliverSmBuilder& params) : Pdu{constants::CMD_ID_DELIVER_SM} {
  m_nCommandStatus = smpp::constants::command_status::ESME_ROK;

  params.checkAllValuesArePresent();
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
  m_nPriorityFlag = params.m_optPriorityFlag.value();
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

std::string DeliverSm::getServiceType() const { return m_strServiceType; }

uint8_t DeliverSm::getSourceAddrTon() const { return m_nSourceAddrTon; }

uint8_t DeliverSm::getSourceAddrNpi() const { return m_nSourceAddrNpi; }

std::string DeliverSm::getSourceAddr() const { return m_strSourceAddr; }

uint8_t DeliverSm::getDestAddrTon() const { return m_nDestAddrTon; }

uint8_t DeliverSm::getDestAddrNpi() const { return m_nDestAddrNpi; }

std::string DeliverSm::getDestinationAddr() const { return m_strDestinationAddr; }

uint8_t DeliverSm::getEsmClass() const { return m_nEsmClass; }

uint8_t DeliverSm::getRegisteredDelivery() const { return m_nRegisteredDelivery; }

uint8_t DeliverSm::getDataCoding() const { return m_nDataCoding; }

void DeliverSm::serialize(std::ostream& os) const {
  Pdu::serialize(os);
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

std::unique_ptr<DeliverSm> DeliverSm::create(std::istream& is) {
  auto deliverSmPtr = std::unique_ptr<DeliverSm>{new DeliverSm{}};

  // std::cout << "DeliverSm::create()";
  const std::string strServiceType = binary::deserializeNullTerminatedString(is);
  deliverSmPtr->m_strServiceType = strServiceType;
  // std::cout << "DeliverSm::create() strServiceType = [" << strServiceType << "]";

  const uint8_t nSourceAddrTon = binary::deserializeInt8(is);
  deliverSmPtr->m_nSourceAddrTon = nSourceAddrTon;
  // std::cout << "DeliverSm::create() nSourceAddrTon = [" << nSourceAddrTon << "]";

  const uint8_t nSourceAddrNpi = binary::deserializeInt8(is);
  deliverSmPtr->m_nSourceAddrNpi = nSourceAddrNpi;
  // std::cout << "DeliverSm::create() nSourceAddrNpi = [" << nSourceAddrNpi << "]";

  const std::string strSourceAddr = binary::deserializeNullTerminatedString(is);
  deliverSmPtr->m_strSourceAddr = strSourceAddr;
  // std::cout << "DeliverSm::create() strSourceAddr = [" << strSourceAddr << "]";

  const uint8_t nDestAddrTon = binary::deserializeInt8(is);
  deliverSmPtr->m_nDestAddrTon = nDestAddrTon;
  // std::cout << "DeliverSm::create() nDestAddrTon = [" << nDestAddrTon << "]";

  const uint8_t nDestAddrNpi = binary::deserializeInt8(is);
  deliverSmPtr->m_nDestAddrNpi = nDestAddrNpi;
  // std::cout << "DeliverSm::create() nDestAddrNpi = [" << nDestAddrNpi << "]";

  const std::string strDestinationAddr = binary::deserializeNullTerminatedString(is);
  deliverSmPtr->m_strDestinationAddr = strDestinationAddr;
  // std::cout << "DeliverSm::create() strDestinationAddr = [" << strDestinationAddr << "]";

  const uint8_t nEsmClass = binary::deserializeInt8(is);
  deliverSmPtr->m_nEsmClass = nEsmClass;
  // std::cout << "DeliverSm::create() nEsmClass = [" << nEsmClass << "]";

  const uint8_t nProtocolId = binary::deserializeInt8(is);
  deliverSmPtr->m_nProtocolId = nProtocolId;
  // std::cout << "DeliverSm::create() nProtocolId = [" << nProtocolId << "]";

  const uint8_t nPriorityFlag = binary::deserializeInt8(is);
  deliverSmPtr->m_nPriorityFlag = nPriorityFlag;
  // std::cout << "DeliverSm::create() nPriorityFlag = [" << nPriorityFlag << "]";

  const std::string strScheduleDeliveryTime = binary::deserializeNullTerminatedString(is);
  deliverSmPtr->m_strScheduleDeliveryTime = strScheduleDeliveryTime;
  // std::cout << "DeliverSm::create() strScheduleDeliveryTime = [" << strScheduleDeliveryTime << "]";

  const std::string strValidityPeriod = binary::deserializeNullTerminatedString(is);
  deliverSmPtr->m_strValidityPeriod = strValidityPeriod;
  // std::cout << "DeliverSm::create() strValidityPeriod = [" << strValidityPeriod << "]";

  const uint8_t nRegisteredDelivery = binary::deserializeInt8(is);
  deliverSmPtr->m_nRegisteredDelivery = nRegisteredDelivery;
  // std::cout << "DeliverSm::create() nRegisteredDelivery = [" << nRegisteredDelivery << "]";

  const uint8_t nReplaceIfPresentFlag = binary::deserializeInt8(is);
  deliverSmPtr->m_nReplaceIfPresentFlag = nReplaceIfPresentFlag;
  // std::cout << "DeliverSm::create() nReplaceIfPresentFlag = [" << nReplaceIfPresentFlag << "]";

  const uint8_t nDataCoding = binary::deserializeInt8(is);
  deliverSmPtr->m_nDataCoding = nDataCoding;
  // std::cout << "DeliverSm::create() nDataCoding = [" << nDataCoding << "]";

  const uint8_t nSmDefaultMsgId = binary::deserializeInt8(is);
  deliverSmPtr->m_nSmDefaultMsgId = nSmDefaultMsgId;
  // std::cout << "DeliverSm::create() nSmDefaultMsgId = [" << nSmDefaultMsgId << "]";

  const uint8_t nSmLength = binary::deserializeInt8(is);
  deliverSmPtr->m_nSmLength = nSmLength;
  // std::cout << "DeliverSm::create() nSmLength = [" << nSmLength << "]";

  const std::string strShortMessage = binary::deserializeOctetString(nSmLength, is);
  deliverSmPtr->m_strShortMessage = strShortMessage;
  // std::cout << "DeliverSm::create() strShortMessage = [" << strShortMessage << "]";

  deliverSmPtr->deserializeOptionalParameters(is);

  return deliverSmPtr;
}

bool DeliverSm::equals(const Pdu& other) const {
  if (!Pdu::equals(other)) {
    return false;
  }

  auto otherDeliverSm = static_cast<const DeliverSm*>(&other);

  return m_strServiceType == otherDeliverSm->m_strServiceType &&
         m_nSourceAddrTon == otherDeliverSm->m_nSourceAddrTon &&
         m_nSourceAddrNpi == otherDeliverSm->m_nSourceAddrNpi &&
         m_strSourceAddr == otherDeliverSm->m_strSourceAddr &&
         m_nDestAddrTon == otherDeliverSm->m_nDestAddrTon &&
         m_nDestAddrNpi == otherDeliverSm->m_nDestAddrNpi &&
         m_strDestinationAddr == otherDeliverSm->m_strDestinationAddr &&
         m_nEsmClass == otherDeliverSm->m_nEsmClass &&
         m_nProtocolId == otherDeliverSm->m_nProtocolId &&
         m_nPriorityFlag == otherDeliverSm->m_nPriorityFlag &&
         m_strScheduleDeliveryTime == otherDeliverSm->m_strScheduleDeliveryTime &&
         m_strValidityPeriod == otherDeliverSm->m_strValidityPeriod &&
         m_nReplaceIfPresentFlag == otherDeliverSm->m_nReplaceIfPresentFlag &&
         m_nDataCoding == otherDeliverSm->m_nDataCoding &&
         m_nSmDefaultMsgId == otherDeliverSm->m_nSmDefaultMsgId &&
         m_nSmLength == otherDeliverSm->m_nSmLength &&
         m_strShortMessage == otherDeliverSm->m_strShortMessage;
}

}  // namespace smpp