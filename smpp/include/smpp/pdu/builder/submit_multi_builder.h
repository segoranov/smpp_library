#ifndef SUBMIT_MULTI_BUILDER_H
#define SUBMIT_MULTI_BUILDER_H

#include <optional>
#include <string>
#include <vector>

#include "smpp/pdu/submit_multi.h"
#include "smpp/tlv/tlv.h"

namespace smpp::builder {

/**
 * Class used for creation of submit_multi PDUs in a more readable and reliable way.
 *
 * The named parameter idiom is used
 * - https://isocpp.org/wiki/faq/ctors#named-parameter-idiom
 * - https://stackoverflow.com/questions/40264/how-many-constructor-arguments-is-too-many
 */
class SubmitMultiBuilder {
 private:
  friend class smpp::SubmitMulti;

  std::optional<uint32_t> m_optSequenceNumber;

  std::optional<std::string> m_optServiceType;
  std::optional<uint8_t> m_optSourceAddrTon;
  std::optional<uint8_t> m_optSourceAddrNpi;
  std::optional<std::string> m_optSourceAddr;
  std::optional<smpp::SubmitMultiDestinationAddresses> m_optDestinationAddresses;
  std::optional<uint8_t> m_optEsmClass;
  std::optional<uint8_t> m_optProtocolId;
  std::optional<uint8_t> m_optPriorityFlag;
  std::optional<std::string> m_optScheduleDeliveryTime;
  std::optional<std::string> m_optValidityPeriod;
  std::optional<uint8_t> m_optRegisteredDelivery;
  std::optional<uint8_t> m_optReplaceIfPresentFlag;
  std::optional<uint8_t> m_optDataCoding;
  std::optional<uint8_t> m_optSmDefaultMsgId;
  std::optional<std::string> m_optShortMessage;

  std::vector<Tlv> m_vOptionalTlvParameters;

  /**
   * @brief Checks to see if all values are present in the optionals
   * @throw UndefinedValueException if some value is not present
   */
  void checkAllValuesArePresent() const;

 public:
  SubmitMultiBuilder() = default;

  SubmitMultiBuilder& withSequenceNumber(uint32_t nSequenceNumber);
  SubmitMultiBuilder& withServiceType(const std::string& strServiceType);
  SubmitMultiBuilder& withSourceAddrTon(uint8_t nSourceAddrTon);
  SubmitMultiBuilder& withSourceAddrNpi(uint8_t nSourceAddrNpi);
  SubmitMultiBuilder& withSourceAddr(const std::string& strSourceAddr);
  SubmitMultiBuilder& withDestinationAddresses(
      const smpp::SubmitMultiDestinationAddresses& destinationAddresses);
  SubmitMultiBuilder& withEsmClass(uint8_t nEsmClass);
  SubmitMultiBuilder& withProtocolId(uint8_t nProtocolId);
  SubmitMultiBuilder& withPriorityFlag(uint8_t nPriorityFlag);
  SubmitMultiBuilder& withScheduleDeliveryTime(const std::string& strScheduleDeliveryTime);
  SubmitMultiBuilder& withValidityPeriod(const std::string& strValidityPeriod);
  SubmitMultiBuilder& withRegisteredDelivery(uint8_t nRegisteredDelivery);
  SubmitMultiBuilder& withReplaceIfPresentFlag(uint8_t nReplaceIfPresentFlag);
  SubmitMultiBuilder& withDataCoding(uint8_t nDataCoding);
  SubmitMultiBuilder& withSmDefaultMsgId(uint8_t nSmDefaultMsgId);
  SubmitMultiBuilder& withShortMessage(const std::string& strShortMessage);
  SubmitMultiBuilder& withOptionalParameters(const std::vector<Tlv>& tlvs);
};

}  // namespace smpp::builder

#endif