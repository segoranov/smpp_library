#ifndef ENQUIRE_LINK_BUILDER_H
#define ENQUIRE_LINK_BUILDER_H

#include <optional>

#include "smpp/pdu/enquire_link.h"

namespace smpp::builder {

/**
 * Class used for creation of enquire link PDUs in a more readable and reliable way.
 *
 * The named parameter idiom is used
 * - https://isocpp.org/wiki/faq/ctors#named-parameter-idiom
 * - https://stackoverflow.com/questions/40264/how-many-constructor-arguments-is-too-many
 */
class EnquireLinkBuilder {
 private:
  friend class smpp::EnquireLink;

  std::optional<uint32_t> m_optSequenceNumber;

  /**
   * @brief Checks to see if all values are present in the optionals
   * @throw UndefinedValueException if some value is not present
   */
  void checkAllValuesArePresent() const;

 public:
  EnquireLinkBuilder() = default;

  EnquireLinkBuilder& withSequenceNumber(uint32_t nSequenceNumber);
};

}  // namespace smpp::builder

#endif