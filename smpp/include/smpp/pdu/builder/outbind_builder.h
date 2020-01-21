#ifndef OUTBIND_BUILDER_H
#define OUTBIND_BUILDER_H

#include <optional>
#include <string>
#include <vector>

#include "smpp/pdu/outbind.h"
#include "smpp/tlv/tlv.h"

namespace smpp::builder {

/**
 * Class used for creation of outbind PDUs in a more readable and reliable way.
 *
 * The named parameter idiom is used
 * - https://isocpp.org/wiki/faq/ctors#named-parameter-idiom
 * - https://stackoverflow.com/questions/40264/how-many-constructor-arguments-is-too-many
 */
class OutbindBuilder {
 private:
  friend class smpp::Outbind;

  std::optional<uint32_t> m_optCommandStatus;
  std::optional<uint32_t> m_optSequenceNumber;
  std::optional<std::string> m_optSystemId;
  std::optional<std::string> m_optPassword;

 public:
  OutbindBuilder() = default;

  OutbindBuilder& withCommandStatus(uint32_t nCommandStatus);
  OutbindBuilder& withSequenceNumber(uint32_t nSequenceNumber);
  OutbindBuilder& withSystemId(const std::string& strSystemId);
  OutbindBuilder& withPassword(const std::string& strPassword);
};

}  // namespace smpp::builder

#endif