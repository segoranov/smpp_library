#include "smpp/pdu/builder/data_sm_builder.h"

namespace smpp::builder {

DataSmBuilder& DataSmBuilder::withCommandStatus(uint32_t nCommandStatus) {
  m_optCommandStatus = nCommandStatus;
  return *this;
}
DataSmBuilder& DataSmBuilder::withSequenceNumber(uint32_t nSequenceNumber) {
  m_optSequenceNumber = nSequenceNumber;
  return *this;
}

DataSmBuilder& DataSmBuilder::withServiceType(const std::string& strServiceType) {
  m_optServiceType = strServiceType;
  return *this;
}

DataSmBuilder& DataSmBuilder::withSourceAddrTon(uint8_t nSourceAddrTon) {
  m_optSourceAddrTon = nSourceAddrTon;
  return *this;
}

DataSmBuilder& DataSmBuilder::withSourceAddrNpi(uint8_t nSourceAddrNpi) {
  m_optSourceAddrNpi = nSourceAddrNpi;
  return *this;
}

DataSmBuilder& DataSmBuilder::withSourceAddr(const std::string& strSourceAddr) {
  m_optSourceAddr = strSourceAddr;
  return *this;
}

DataSmBuilder& DataSmBuilder::withDestAddrTon(uint8_t nDestAddrTon) {
  m_optDestAddrTon = nDestAddrTon;
  return *this;
}

DataSmBuilder& DataSmBuilder::withDestAddrNpi(uint8_t nDestAddrNpi) {
  m_optDestAddrNpi = nDestAddrNpi;
  return *this;
}

DataSmBuilder& DataSmBuilder::withDestinationAddr(const std::string& strDestinationAddr) {
  m_optDestinationAddr = strDestinationAddr;
  return *this;
}

DataSmBuilder& DataSmBuilder::withEsmClass(uint8_t nEsmClass) {
  m_optEsmClass = nEsmClass;
  return *this;
}

DataSmBuilder& DataSmBuilder::withRegisteredDelivery(uint8_t nRegisteredDelivery) {
  m_optRegisteredDelivery = nRegisteredDelivery;
  return *this;
}

DataSmBuilder& DataSmBuilder::withDataCoding(uint8_t nDataCoding) {
  m_optDataCoding = nDataCoding;
  return *this;
}

DataSmBuilder& DataSmBuilder::withOptionalParameters(const std::vector<Tlv>& tlvs) {
  m_vOptionalTlvParameters = tlvs;
  return *this;
}

}  // namespace smpp::builder