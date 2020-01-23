#include "smpp/pdu/data_sm.h"

#include "smpp/pdu/builder/data_sm_builder.h"
#include "smpp/util/logging.h"
#include "smpp/util/serialization_util.h"

namespace smpp {

DataSm::DataSm() : Pdu{constants::CMD_ID_DATA_SM} {}

DataSm::DataSm(const builder::DataSmBuilder& params) : Pdu{constants::CMD_ID_DATA_SM} {
  if (!params.m_optCommandStatus.has_value()) {
    throw UndefinedValueException("DataSm(): Undefined command status");
  }

  if (!params.m_optSequenceNumber.has_value()) {
    throw UndefinedValueException("DataSm(): Undefined sequence number");
  }

  if (!params.m_optServiceType.has_value()) {
    throw UndefinedValueException("DataSm(): Undefined service type");
  }

  if (!params.m_optSourceAddrTon.has_value()) {
    throw UndefinedValueException("DataSm(): Undefined source addr ton");
  }

  if (!params.m_optSourceAddrNpi.has_value()) {
    throw UndefinedValueException("DataSm(): Undefined source addr npi");
  }

  if (!params.m_optSourceAddr.has_value()) {
    throw UndefinedValueException("DataSm(): Undefined source addr");
  }

  if (!params.m_optDestAddrTon.has_value()) {
    throw UndefinedValueException("DataSm(): Undefined dest addr ton");
  }

  if (!params.m_optDestAddrNpi.has_value()) {
    throw UndefinedValueException("DataSm(): Undefined dest addr npi");
  }

  if (!params.m_optDestinationAddr.has_value()) {
    throw UndefinedValueException("DataSm(): Undefined destination addr");
  }

  if (!params.m_optEsmClass.has_value()) {
    throw UndefinedValueException("DataSm(): Undefined esm class");
  }

  if (!params.m_optRegisteredDelivery.has_value()) {
    throw UndefinedValueException("DataSm(): Undefined registered delivery");
  }

  if (!params.m_optDataCoding.has_value()) {
    throw UndefinedValueException("DataSm(): Undefined data coding");
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
  m_nRegisteredDelivery = params.m_optRegisteredDelivery.value();
  m_nDataCoding = params.m_optDataCoding.value();
  m_vOptionalTlvParameters = params.m_vOptionalTlvParameters;

  // Add PDU header to command length
  m_nCommandLength = smpp::constants::PDU_HEADER_LENGTH;

  // Add C-octet strings to command length without forgetting to add 1
  // for the null terminating character
  m_nCommandLength += m_strServiceType.size() + 1;
  m_nCommandLength += m_strSourceAddr.size() + 1;
  m_nCommandLength += m_strDestinationAddr.size() + 1;

  // 7 more mandatory fields with size 1 byte
  m_nCommandLength += 7;

  // Add optional parameters size to command length
  for (const auto& tlv : m_vOptionalTlvParameters) {
    m_nCommandLength += tlv.size();
  }
}

std::string DataSm::getServiceType() const { return m_strServiceType; }

uint8_t DataSm::getSourceAddrTon() const { return m_nSourceAddrTon; }

uint8_t DataSm::getSourceAddrNpi() const { return m_nSourceAddrNpi; }

std::string DataSm::getSourceAddr() const { return m_strSourceAddr; }

uint8_t DataSm::getDestAddrTon() const { return m_nDestAddrTon; }

uint8_t DataSm::getDestAddrNpi() const { return m_nDestAddrNpi; }

std::string DataSm::getDestinationAddr() const { return m_strDestinationAddr; }

uint8_t DataSm::getEsmClass() const { return m_nEsmClass; }

uint8_t DataSm::getRegisteredDelivery() const { return m_nRegisteredDelivery; }

uint8_t DataSm::getDataCoding() const { return m_nDataCoding; }

void DataSm::serializeBody(std::ostream& os) const {
  binary::serializeNullTerminatedString(m_strServiceType, os);
  binary::serializeInt8(m_nSourceAddrTon, os);
  binary::serializeInt8(m_nSourceAddrNpi, os);
  binary::serializeNullTerminatedString(m_strSourceAddr, os);
  binary::serializeInt8(m_nDestAddrTon, os);
  binary::serializeInt8(m_nDestAddrNpi, os);
  binary::serializeNullTerminatedString(m_strDestinationAddr, os);
  binary::serializeInt8(m_nEsmClass, os);
  binary::serializeInt8(m_nRegisteredDelivery, os);
  binary::serializeInt8(m_nDataCoding, os);
  serializeOptionalParameters(os);  // optional parameters are part of the body
}

void DataSm::deserializeBody(std::istream& is) {
  INFO << "DataSm::deserializeBody()";
  const std::string strServiceType = binary::deserializeNullTerminatedString(is);
  m_strServiceType = strServiceType;
  DEBUG << "DataSm::deserializeBody() strServiceType = [" << strServiceType << "]";

  const uint8_t nSourceAddrTon = binary::deserializeInt8(is);
  m_nSourceAddrTon = nSourceAddrTon;
  DEBUG << "DataSm::deserializeBody() nSourceAddrTon = [" << nSourceAddrTon << "]";

  const uint8_t nSourceAddrNpi = binary::deserializeInt8(is);
  m_nSourceAddrNpi = nSourceAddrNpi;
  DEBUG << "DataSm::deserializeBody() nSourceAddrNpi = [" << nSourceAddrNpi << "]";

  const std::string strSourceAddr = binary::deserializeNullTerminatedString(is);
  m_strSourceAddr = strSourceAddr;
  DEBUG << "DataSm::deserializeBody() strSourceAddr = [" << strSourceAddr << "]";

  const uint8_t nDestAddrTon = binary::deserializeInt8(is);
  m_nDestAddrTon = nDestAddrTon;
  DEBUG << "DataSm::deserializeBody() nDestAddrTon = [" << nDestAddrTon << "]";

  const uint8_t nDestAddrNpi = binary::deserializeInt8(is);
  m_nDestAddrNpi = nDestAddrNpi;
  DEBUG << "DataSm::deserializeBody() nDestAddrNpi = [" << nDestAddrNpi << "]";

  const std::string strDestinationAddr = binary::deserializeNullTerminatedString(is);
  m_strDestinationAddr = strDestinationAddr;
  DEBUG << "DataSm::deserializeBody() strDestinationAddr = [" << strDestinationAddr << "]";

  const uint8_t nEsmClass = binary::deserializeInt8(is);
  m_nEsmClass = nEsmClass;
  DEBUG << "DataSm::deserializeBody() nEsmClass = [" << nEsmClass << "]";

  const uint8_t nRegisteredDelivery = binary::deserializeInt8(is);
  m_nRegisteredDelivery = nRegisteredDelivery;
  DEBUG << "DataSm::deserializeBody() nRegisteredDelivery = [" << nRegisteredDelivery << "]";

  const uint8_t nDataCoding = binary::deserializeInt8(is);
  m_nDataCoding = nDataCoding;
  DEBUG << "DataSm::deserializeBody() nDataCoding = [" << nDataCoding << "]";

  deserializeOptionalParameters(is);
}

void DataSm::serialize(std::ostream& os) const {
  serializeHeader(os);
  serializeBody(os);
}

std::unique_ptr<DataSm> DataSm::createPduBody(std::istream& is) {
  auto dataSmPtr = std::unique_ptr<DataSm>{new DataSm{}};
  dataSmPtr->deserializeBody(is);
  return dataSmPtr;
}

}  // namespace smpp