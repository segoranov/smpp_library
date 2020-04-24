#include "smpp/pdu/submit_multi.h"

#include <sstream>

#include "smpp/pdu/builder/submit_multi_builder.h"
#include "smpp/smpp_exceptions.h"
#include "smpp/util/serialization_util.h"

namespace smpp {

SMEDestAddress::SMEDestAddress(uint8_t nDestAddrTon, uint8_t nDestAddrNpi,
                               const std::string& strDestinationAddr)
    : m_nDestAddrTon{nDestAddrTon}, m_nDestAddrNpi{nDestAddrNpi} {
  if (strDestinationAddr.size() > 21) {
    std::stringstream error;
    error << "'destination_addr' max size is 21 bytes. Number of bytes received are: ["
          << strDestinationAddr.size() << "]";
    throw FieldOutOfRangeException(error.str());
  }

  m_strDestinationAddr = strDestinationAddr;
}

SMEDestAddress& SMEDestAddress::operator=(const SMEDestAddress& other) {
  if (this != &other) {
    m_nDestAddrTon = other.m_nDestAddrTon;
    m_nDestAddrNpi = other.m_nDestAddrNpi;
    m_strDestinationAddr = other.m_strDestinationAddr;
  }
  return *this;
}

uint8_t SMEDestAddress::getDestAddrTon() const { return m_nDestAddrTon; }

uint8_t SMEDestAddress::getDestAddrNpi() const { return m_nDestAddrNpi; }

std::string SMEDestAddress::getDestinationAddr() const { return m_strDestinationAddr; }

int SMEDestAddress::size() const { return 3 + m_strDestinationAddr.size() + 1; }

DistributionListDestAddress::DistributionListDestAddress(const std::string& strDlName) {
  if (strDlName.size() > 21) {
    std::stringstream error;
    error << "'dl_name' max size is 21 bytes. Number of bytes received are: [" << strDlName.size()
          << "]";
    throw FieldOutOfRangeException(error.str());
  }

  m_strDlName = strDlName;
}

DistributionListDestAddress& DistributionListDestAddress::operator=(
    const DistributionListDestAddress& other) {
  if (this != &other) {
    m_strDlName = other.m_strDlName;
  }
  return *this;
}

std::string DistributionListDestAddress::getDlName() const { return m_strDlName; }

int DistributionListDestAddress::size() const { return 1 + m_strDlName.size() + 1; }

uint8_t SubmitMultiDestinationAddresses::getNumberOfDests() const { return m_nNumberOfDests; }

std::vector<SMEDestAddress> SubmitMultiDestinationAddresses::getSMEDestAddresses() const {
  return m_vSMEDestAddresses;
}

std::vector<DistributionListDestAddress>
SubmitMultiDestinationAddresses::getDistributionListDestAddresses() const {
  return m_vDistributionListDestAddresses;
}

void SubmitMultiDestinationAddresses::addSMEDestAddress(const SMEDestAddress& addr) {
  if (m_nNumberOfDests == 255) {
    throw FieldOutOfRangeException("Cannot add anymore SME destination addresses");
  }
  m_nNumberOfDests++;
  m_vSMEDestAddresses.push_back(addr);
}

void SubmitMultiDestinationAddresses::addDistributionListDestAddress(
    const DistributionListDestAddress& addr) {
  if (m_nNumberOfDests == 255) {
    throw FieldOutOfRangeException("Cannot add anymore Distribution List destination addresses");
  }
  m_nNumberOfDests++;
  m_vDistributionListDestAddresses.push_back(addr);
}

int SubmitMultiDestinationAddresses::size() const {
  auto result{0};

  result += 1;  // number_of_dests field

  for (auto const& smeDestAddress : m_vSMEDestAddresses) {
    result += smeDestAddress.size();
  }

  for (auto const& distributionListAddress : m_vDistributionListDestAddresses) {
    result += distributionListAddress.size();
  }

  return result;
}

std::string SubmitMultiDestinationAddresses::toString() const {
  return "SubmitMultiDestinationAddresses::toString()";  // TODO SG
}

void SubmitMultiDestinationAddresses::serialize(std::ostream& os) const {
  // std::cout << "SubmitMultiDestinationAddresses::serialize()";
  binary::serializeInt8(m_nNumberOfDests, os);

  for (auto const& smeDestAddress : m_vSMEDestAddresses) {
    binary::serializeInt8(constants::SME_FORMAT_DESTINATION_ADDRESS, os);
    binary::serializeInt8(smeDestAddress.getDestAddrTon(), os);
    binary::serializeInt8(smeDestAddress.getDestAddrNpi(), os);
    binary::serializeNullTerminatedString(smeDestAddress.getDestinationAddr(), os);
  }

  for (auto const& distributionListAddress : m_vDistributionListDestAddresses) {
    binary::serializeInt8(constants::DISTRIBUTION_LIST_FORMAT_DESTINATION_ADDRESS, os);
    binary::serializeNullTerminatedString(distributionListAddress.getDlName(), os);
  }
}

void SubmitMultiDestinationAddresses::deserialize(std::istream& is) {
  // std::cout << "SubmitMultiDestinationAddresses::deserialize()";

  const uint8_t nNumberOfDests = binary::deserializeInt8(is);

  for (int dest = 0; dest < nNumberOfDests; ++dest) {
    const uint8_t nDestFlag = binary::deserializeInt8(is);
    switch (nDestFlag) {
      case constants::SME_FORMAT_DESTINATION_ADDRESS: {
        const uint8_t nDestAddrTon = binary::deserializeInt8(is);
        const uint8_t nDestAddrNpi = binary::deserializeInt8(is);
        const std::string strDestinationAddr = binary::deserializeNullTerminatedString(is);
        addSMEDestAddress(SMEDestAddress{nDestAddrTon, nDestAddrNpi, strDestinationAddr});
        break;
      }
      case constants::DISTRIBUTION_LIST_FORMAT_DESTINATION_ADDRESS: {
        const std::string strDlName = binary::deserializeNullTerminatedString(is);
        addDistributionListDestAddress(DistributionListDestAddress{strDlName});
        break;
      }
      default: {
        std::stringstream error;
        error << "Invalid 'dest_flag' - [ " << nDestFlag
              << "] detected during deserialization of destination addresses";
        throw InvalidFieldException(error.str());
      }
    }
  }
}

SubmitMulti::SubmitMulti() : BaseSubmit{constants::CMD_ID_SUBMIT_MULTI} {}

SubmitMulti::SubmitMulti(const builder::SubmitMultiBuilder& params)
    : BaseSubmit{constants::CMD_ID_SUBMIT_MULTI} {
  // std::cout << "SubmitMulti(builder) constructor";
  params.checkAllValuesArePresent();
  m_nSequenceNumber = params.m_optSequenceNumber.value();
  m_strServiceType = params.m_optServiceType.value();
  m_nSourceAddrTon = params.m_optSourceAddrTon.value();
  m_nSourceAddrNpi = params.m_optSourceAddrNpi.value();
  m_strSourceAddr = params.m_optSourceAddr.value();
  m_destinationAddresses = params.m_optDestinationAddresses.value();
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
  m_nCommandLength += m_strScheduleDeliveryTime.size() + 1;
  m_nCommandLength += m_strValidityPeriod.size() + 1;
  m_nCommandLength += m_strShortMessage.size();  // short message is not null terminated

  // Add destination addresses' size to command length
  m_nCommandLength += m_destinationAddresses.size();

  // 10 more mandatory fields with size 1 byte
  m_nCommandLength += 10;

  // Add optional parameters size to command length
  for (const auto& tlv : m_vOptionalTlvParameters) {
    m_nCommandLength += tlv.size();
  }
}

SubmitMultiDestinationAddresses SubmitMulti::getDestinationAddresses() const {
  return m_destinationAddresses;
}

void SubmitMulti::serialize(std::ostream& os) const {
  // std::cout << "SubmitMulti::serialize()";
  Pdu::serialize(os);
  binary::serializeNullTerminatedString(m_strServiceType, os);
  binary::serializeInt8(m_nSourceAddrTon, os);
  binary::serializeInt8(m_nSourceAddrNpi, os);
  binary::serializeNullTerminatedString(m_strSourceAddr, os);
  m_destinationAddresses.serialize(os);
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

std::unique_ptr<SubmitMulti> SubmitMulti::create(std::istream& is) {
  // std::cout << "SubmitMulti::create()";
  auto submitMultiPtr = std::unique_ptr<SubmitMulti>{new SubmitMulti{}};

  // std::cout << "SubmitMulti::create()";

  const std::string strServiceType = binary::deserializeNullTerminatedString(is);
  submitMultiPtr->m_strServiceType = strServiceType;
  // std::cout << "SubmitMulti::create() strServiceType = [" << strServiceType << "]";

  const uint8_t nSourceAddrTon = binary::deserializeInt8(is);
  submitMultiPtr->m_nSourceAddrTon = nSourceAddrTon;
  // std::cout << "SubmitMulti::create() nSourceAddrTon = [" << nSourceAddrTon << "]";

  const uint8_t nSourceAddrNpi = binary::deserializeInt8(is);
  submitMultiPtr->m_nSourceAddrNpi = nSourceAddrNpi;
  // std::cout << "SubmitMulti::create() nSourceAddrTon = [" << nSourceAddrTon << "]";

  const std::string strSourceAddr = binary::deserializeNullTerminatedString(is);
  submitMultiPtr->m_strSourceAddr = strSourceAddr;
  // std::cout << "SubmitMulti::create() nSourceAddrTon = [" << nSourceAddrTon << "]";

  SubmitMultiDestinationAddresses destinationAddresses;
  destinationAddresses.deserialize(is);
  // std::cout << "SubmitMulti::create() destinationAddresses = [" <<
  // destinationAddresses.toString()
  // << "]";
  submitMultiPtr->m_destinationAddresses = destinationAddresses;

  const uint8_t nEsmClass = binary::deserializeInt8(is);
  submitMultiPtr->m_nEsmClass = nEsmClass;
  // std::cout << "SubmitMulti::create() nEsmClass = [" << nEsmClass << "]";

  const uint8_t nProtocolId = binary::deserializeInt8(is);
  submitMultiPtr->m_nProtocolId = nProtocolId;
  // std::cout << "SubmitMulti::create() nProtocolId = [" << nProtocolId << "]";

  const uint8_t nPriorityFlag = binary::deserializeInt8(is);
  submitMultiPtr->m_nPriorityFlag = nPriorityFlag;
  // std::cout << "SubmitMulti::create() nPriorityFlag = [" << nPriorityFlag << "]";

  const std::string strScheduleDeliveryTime = binary::deserializeNullTerminatedString(is);
  submitMultiPtr->m_strScheduleDeliveryTime = strScheduleDeliveryTime;
  // std::cout << "SubmitMulti::create() strScheduleDeliveryTime = [" << strScheduleDeliveryTime <<
  // "]";

  const std::string strValidityPeriod = binary::deserializeNullTerminatedString(is);
  submitMultiPtr->m_strValidityPeriod = strValidityPeriod;
  // std::cout << "SubmitMulti::create() strValidityPeriod = [" << strValidityPeriod << "]";

  const uint8_t nRegisteredDelivery = binary::deserializeInt8(is);
  submitMultiPtr->m_nRegisteredDelivery = nRegisteredDelivery;
  // std::cout << "SubmitMulti::create() nRegisteredDelivery = [" << nRegisteredDelivery << "]";

  const uint8_t nReplaceIfPresentFlag = binary::deserializeInt8(is);
  submitMultiPtr->m_nReplaceIfPresentFlag = nReplaceIfPresentFlag;
  // std::cout << "SubmitMulti::create() nReplaceIfPresentFlag = [" << nReplaceIfPresentFlag <<
  // "]";

  const uint8_t nDataCoding = binary::deserializeInt8(is);
  submitMultiPtr->m_nDataCoding = nDataCoding;
  // std::cout << "SubmitMulti::create() nDataCoding = [" << nDataCoding << "]";

  const uint8_t nSmDefaultMsgId = binary::deserializeInt8(is);
  submitMultiPtr->m_nSmDefaultMsgId = nSmDefaultMsgId;
  // std::cout << "SubmitMulti::create() nSmDefaultMsgId = [" << nSmDefaultMsgId << "]";

  const uint8_t nSmLength = binary::deserializeInt8(is);
  submitMultiPtr->m_nSmLength = nSmLength;
  // std::cout << "SubmitMulti::create() nSmLength = [" << nSmLength << "]";

  const std::string strShortMessage = binary::deserializeOctetString(nSmLength, is);
  submitMultiPtr->m_strShortMessage = strShortMessage;
  // std::cout << "SubmitMulti::create() strShortMessage = [" << strShortMessage << "]";

  submitMultiPtr->deserializeOptionalParameters(is);

  return submitMultiPtr;
}

bool operator==(const smpp::SMEDestAddress& lhs, const smpp::SMEDestAddress& rhs) {
  return lhs.getDestAddrNpi() == rhs.getDestAddrNpi() &&
         lhs.getDestAddrTon() == rhs.getDestAddrTon() &&
         lhs.getDestinationAddr() == rhs.getDestinationAddr();
}

bool operator==(const DistributionListDestAddress& lhs, const DistributionListDestAddress& rhs) {
  return lhs.getDlName() == rhs.getDlName();
}

bool operator==(const SubmitMultiDestinationAddresses& lhs,
                const SubmitMultiDestinationAddresses& rhs) {
  return lhs.getNumberOfDests() == rhs.getNumberOfDests() &&
         lhs.getSMEDestAddresses() == rhs.getSMEDestAddresses() &&
         lhs.getDistributionListDestAddresses() == rhs.getDistributionListDestAddresses();
}

bool operator!=(const smpp::SMEDestAddress& lhs, const smpp::SMEDestAddress& rhs) {
  return !(lhs == rhs);
}

bool operator!=(const DistributionListDestAddress& lhs, const DistributionListDestAddress& rhs) {
  return !(lhs == rhs);
}

bool operator!=(const SubmitMultiDestinationAddresses& lhs,
                const SubmitMultiDestinationAddresses& rhs) {
  return !(lhs == rhs);
}

}  // namespace smpp
