#ifndef SUBMIT_SM_RESP_BUILDER_H
#define SUBMIT_SM_RESP_BUILDER_H

#include <optional>
#include <string>
#include <vector>

#include "smpp/pdu/submit_sm_resp.h"
#include "smpp/tlv/tlv.h"

namespace smpp::builder {

/**
 * Class used for creation of submit_sm_resp PDUs in a more readable and reliable way.
 *
 * The named parameter idiom is used
 * - https://isocpp.org/wiki/faq/ctors#named-parameter-idiom
 * - https://stackoverflow.com/questions/40264/how-many-constructor-arguments-is-too-many
 */
class SubmitSmRespBuilder {
 private:
  friend class smpp::SubmitSmResp;

  std::optional<uint32_t> m_optCommandStatus;
  std::optional<uint32_t> m_optSequenceNumber;

  std::optional<std::string> m_optMessageId;

  std::vector<Tlv> m_vOptionalTlvParameters;

  /**
   * @brief Checks to see if all values are present in the optionals
   * @throw UndefinedValueException if some value is not present
   */
  void checkAllValuesArePresent() const;

 public:
  SubmitSmRespBuilder() = default;

  SubmitSmRespBuilder& withCommandStatus(uint32_t nCommandStatus);
  SubmitSmRespBuilder& withSequenceNumber(uint32_t nSequenceNumber);
  SubmitSmRespBuilder& withMessageId(const std::string& strMessageId);
  SubmitSmRespBuilder& withOptionalParameters(const std::vector<Tlv>& tlvs);
};

}  // namespace smpp::builder

#endif