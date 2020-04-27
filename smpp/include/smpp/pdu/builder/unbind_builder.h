#ifndef UNBIND_BUILDER_H
#define UNBIND_BUILDER_H

#include <optional>

#include "smpp/pdu/unbind.h"

namespace smpp::builder {

/**
 * Class used for creation of unbind PDUs in a more readable and reliable way.
 *
 * The named parameter idiom is used
 * - https://isocpp.org/wiki/faq/ctors#named-parameter-idiom
 * - https://stackoverflow.com/questions/40264/how-many-constructor-arguments-is-too-many
 */
class UnbindBuilder {
 private:
  friend class smpp::Unbind;

  std::optional<uint32_t> m_optSequenceNumber;

  /**
   * @brief Checks to see if all values are present in the optionals
   * @throw UndefinedValueException if some value is not present
   */
  void checkAllValuesArePresent() const;

 public:
  UnbindBuilder() = default;

  UnbindBuilder& withSequenceNumber(uint32_t nSequenceNumber);
};

}  // namespace smpp::builder

#endif