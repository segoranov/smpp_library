#ifndef DELIVER_SM_BUILDER_H
#define DELIVER_SM_BUILDER_H

#include <optional>
#include <string>
#include <vector>

#include "smpp/pdu/deliver_sm.h"
#include "smpp/tlv/tlv.h"

namespace smpp::builder {

/**
 * Class used for creation of deliver_sm PDUs in a more readable and reliable way.
 *
 * The named parameter idiom is used
 * - https://isocpp.org/wiki/faq/ctors#named-parameter-idiom
 * - https://stackoverflow.com/questions/40264/how-many-constructor-arguments-is-too-many
 */
class DeliverSmBuilder {
 private:
  friend class smpp::DeliverSm;

  std::optional<uint32_t> m_optSequenceNumber;

  std::optional<std::string> m_optServiceType;
  std::optional<uint8_t> m_optSourceAddrTon;
  std::optional<uint8_t> m_optSourceAddrNpi;
  std::optional<std::string> m_optSourceAddr;

  std::optional<uint8_t> m_optDestAddrTon;
  std::optional<uint8_t> m_optDestAddrNpi;
  std::optional<std::string> m_optDestinationAddr;

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
  DeliverSmBuilder() = default;

  DeliverSmBuilder& withSequenceNumber(uint32_t nSequenceNumber);
  DeliverSmBuilder& withServiceType(const std::string& strServiceType);
  DeliverSmBuilder& withSourceAddrTon(uint8_t nSourceAddrTon);
  DeliverSmBuilder& withSourceAddrNpi(uint8_t nSourceAddrNpi);
  DeliverSmBuilder& withSourceAddr(const std::string& strSourceAddr);
  DeliverSmBuilder& withDestAddrTon(uint8_t nDestAddrTon);
  DeliverSmBuilder& withDestAddrNpi(uint8_t nDestAddrNpi);
  DeliverSmBuilder& withDestinationAddr(const std::string& strDestinationAddr);
  DeliverSmBuilder& withEsmClass(uint8_t nEsmClass);
  DeliverSmBuilder& withProtocolId(uint8_t nProtocolId);
  DeliverSmBuilder& withPriorityFlag(uint8_t nPriorityFlag);
  DeliverSmBuilder& withScheduleDeliveryTime(const std::string& strScheduleDeliveryTime);
  DeliverSmBuilder& withValidityPeriod(const std::string& strValidityPeriod);
  DeliverSmBuilder& withRegisteredDelivery(uint8_t nRegisteredDelivery);
  DeliverSmBuilder& withReplaceIfPresentFlag(uint8_t nReplaceIfPresentFlag);
  DeliverSmBuilder& withDataCoding(uint8_t nDataCoding);
  DeliverSmBuilder& withSmDefaultMsgId(uint8_t nSmDefaultMsgId);
  DeliverSmBuilder& withShortMessage(const std::string& strShortMessage);
  DeliverSmBuilder& withOptionalParameters(const std::vector<Tlv>& tlvs);
};

}  // namespace smpp::builder

#endif