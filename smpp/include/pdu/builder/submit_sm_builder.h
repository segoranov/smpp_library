#ifndef SUBMIT_SM_BUILDER_H
#define SUBMIT_SM_BUILDER_H

#include <optional>
#include <string>
#include <vector>

#include "pdu/submit_sm.h"
#include "tlv/tlv.h"

namespace smpp::builder {

/**
 * Class used for creation of submit_sm PDUs in a more readable and reliable way.
 * Forces all objects to have their fields defined.
 *
 * The named parameter idiom is used
 * - https://isocpp.org/wiki/faq/ctors#named-parameter-idiom
 * - https://stackoverflow.com/questions/40264/how-many-constructor-arguments-is-too-many
 */
class SubmitSmBuilder {
 private:
  friend class smpp::SubmitSm;

  std::optional<uint32_t> m_optCommandLength;
  uint32_t m_nCommandId;
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
  std::optional<uint8_t> m_optProtocolId;
  std::optional<uint8_t> m_optPriorityFlag;
  std::optional<std::string> m_optScheduleDeliveryTime;
  std::optional<std::string> m_optValidityPeriod;
  std::optional<uint8_t> m_optRegisteredDelivery;
  std::optional<uint8_t> m_optReplaceIfPresentFlag;
  std::optional<uint8_t> m_optDataCoding;
  std::optional<uint8_t> m_optSmDefaultMsgId;
  std::optional<uint8_t> m_optSmLength;
  std::optional<std::string> m_optShortMessage;

  std::vector<Tlv> m_vOptionalTlvParameters;

 public:
  SubmitSmBuilder();

  SubmitSmBuilder& withCommandLength(uint32_t nCommandLength);
  SubmitSmBuilder& withCommandStatus(uint32_t nCommandStatus);
  SubmitSmBuilder& withSequenceNumber(uint32_t nSequenceNumber);
  SubmitSmBuilder& withServiceType(const std::string& strServiceType);
  SubmitSmBuilder& withSourceAddrTon(uint8_t nSourceAddrTon);
  SubmitSmBuilder& withSourceAddrNpi(uint8_t nSourceAddrNpi);
  SubmitSmBuilder& withSourceAddr(const std::string& strSourceAddr);
  SubmitSmBuilder& withDestAddrTon(uint8_t nDestAddrTon);
  SubmitSmBuilder& withDestAddrNpi(uint8_t nDestAddrNpi);
  SubmitSmBuilder& withDestinationAddr(const std::string& strDestinationAddr);
  SubmitSmBuilder& withEsmClass(uint8_t nEsmClass);
  SubmitSmBuilder& withProtocolId(uint8_t nProtocolId);
  SubmitSmBuilder& withPriorityFlag(uint8_t nPriorityFlag);
  SubmitSmBuilder& withScheduleDeliveryTime(const std::string& strScheduleDeliveryTime);
  SubmitSmBuilder& withValidityPeriod(const std::string& strValidityPeriod);
  SubmitSmBuilder& withRegisteredDelivery(uint8_t nRegisteredDelivery);
  SubmitSmBuilder& withReplaceIfPresentFlag(uint8_t nReplaceIfPresentFlag);
  SubmitSmBuilder& withDataCoding(uint8_t nDataCoding);
  SubmitSmBuilder& withSmDefaultMsgId(uint8_t nSmDefaultMsgId);
  SubmitSmBuilder& withSmLength(uint8_t nSmLength);
  SubmitSmBuilder& withShortMessage(const std::string& strShortMessage);
  SubmitSmBuilder& withOptionalParameters(const std::vector<Tlv>& tlvs);
};

}  // namespace smpp::builder

#endif