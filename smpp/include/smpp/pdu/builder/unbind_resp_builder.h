#ifndef UNBIND_RESP_BUILDER_H
#define UNBIND_RESP_BUILDER_H

#include <optional>

#include "smpp/pdu/unbind_resp.h"

namespace smpp::builder {

/**
 * Class used for creation of unbind resp PDUs in a more readable and reliable way.
 *
 * The named parameter idiom is used
 * - https://isocpp.org/wiki/faq/ctors#named-parameter-idiom
 * - https://stackoverflow.com/questions/40264/how-many-constructor-arguments-is-too-many
 */
class UnbindRespBuilder {
 private:
  friend class smpp::UnbindResp;

  std::optional<uint32_t> m_optCommandStatus;
  std::optional<uint32_t> m_optSequenceNumber;

  /**
   * @brief Checks to see if all values are present in the optionals
   * @throw UndefinedValueException if some value is not present
   */
  void checkAllValuesArePresent() const;

 public:
  UnbindRespBuilder() = default;

  UnbindRespBuilder& withCommandStatus(uint32_t nCommandStatus);
  UnbindRespBuilder& withSequenceNumber(uint32_t nSequenceNumber);
};

}  // namespace smpp::builder

#endif
