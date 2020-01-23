#ifndef DATA_SM_BUILDER_H
#define DATA_SM_BUILDER_H

#include <optional>
#include <string>
#include <vector>

#include "smpp/pdu/data_sm.h"
#include "smpp/tlv/tlv.h"

namespace smpp::builder {

/**
 * Class used for creation of data_sm PDUs in a more readable and reliable way.
 *
 * The named parameter idiom is used
 * - https://isocpp.org/wiki/faq/ctors#named-parameter-idiom
 * - https://stackoverflow.com/questions/40264/how-many-constructor-arguments-is-too-many
 */
class DataSmBuilder {
 private:
  friend class smpp::DataSm;

  std::optional<uint32_t> m_optCommandStatus;
  std::optional<uint32_t> m_optSequenceNumber;
  std::optional<std::string> m_optServiceType;
  std::optional<uint8_t> m_optSourceAddrTon;
  std::optional<uint8_t> m_optSourceAddrNpi;
  std::optional<std::string> m_optSourceAddr;
  std::optional<uint8_t> m_optDestAddrTon;
  std::optional<uint8_t> m_optDestAddrNpi;
  std::optional<std::string> m_optDestinationAddr;
  std::optional<uint8_t> m_optEsmClass;
  std::optional<uint8_t> m_optRegisteredDelivery;
  std::optional<uint8_t> m_optDataCoding;
  std::vector<Tlv> m_vOptionalTlvParameters;

  /**
   * @brief Checks to see if all values are present in the optionals
   * @throw UndefinedValueException if some value is not present
   */
  void checkAllValuesArePresent() const;

 public:
  DataSmBuilder() = default;

  DataSmBuilder& withCommandStatus(uint32_t nCommandStatus);
  DataSmBuilder& withSequenceNumber(uint32_t nSequenceNumber);
  DataSmBuilder& withServiceType(const std::string& strServiceType);
  DataSmBuilder& withSourceAddrTon(uint8_t nSourceAddrTon);
  DataSmBuilder& withSourceAddrNpi(uint8_t nSourceAddrNpi);
  DataSmBuilder& withSourceAddr(const std::string& strSourceAddr);
  DataSmBuilder& withDestAddrTon(uint8_t nDestAddrTon);
  DataSmBuilder& withDestAddrNpi(uint8_t nDestAddrNpi);
  DataSmBuilder& withDestinationAddr(const std::string& strDestinationAddr);
  DataSmBuilder& withEsmClass(uint8_t nEsmClass);
  DataSmBuilder& withRegisteredDelivery(uint8_t nRegisteredDelivery);
  DataSmBuilder& withDataCoding(uint8_t nDataCoding);
  DataSmBuilder& withOptionalParameters(const std::vector<Tlv>& tlvs);
};

}  // namespace smpp::builder

#endif