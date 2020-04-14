#ifndef BIND_BUILDER_H
#define BIND_BUILDER_H

#include <optional>
#include <string>
#include <vector>

#include "smpp/pdu/pdu.h"
#include "smpp/tlv/tlv.h"

namespace smpp {

template <uint32_t CommandId>
class Bind;

}  // namespace smpp

namespace smpp::builder {

/**
 * Class used for creation of bind PDUs in a more readable and reliable way.
 * - bind_transmitter
 * - bind transceiver
 * - bind_transceiver
 *
 * The named parameter idiom is used
 * - https://isocpp.org/wiki/faq/ctors#named-parameter-idiom
 * - https://stackoverflow.com/questions/40264/how-many-constructor-arguments-is-too-many
 */
class BindBuilder {
 private:
  template <uint32_t CommandId>
  friend class smpp::Bind;

  std::optional<uint32_t> m_optSequenceNumber;

  std::optional<std::string> m_optSystemId;
  std::optional<std::string> m_optPassword;
  std::optional<std::string> m_optSystemType;
  std::optional<uint8_t> m_optInterfaceVersion;
  std::optional<uint8_t> m_optAddrTon;
  std::optional<uint8_t> m_optAddrNpi;
  std::optional<std::string> m_optAddressRange;

  /**
   * @brief Checks to see if all values are present in the optionals
   * @throw UndefinedValueException if some value is not present
   */
  void checkAllValuesArePresent() const;

 public:
  BindBuilder() = default;

  BindBuilder& withSequenceNumber(uint32_t nSequenceNumber);
  BindBuilder& withSystemId(const std::string& strSystemId);
  BindBuilder& withPassword(const std::string& strPassword);
  BindBuilder& withSystemType(const std::string& strSystemType);
  BindBuilder& withInterfaceVersion(uint8_t nInterfaceVersion);
  BindBuilder& withAddrTon(uint8_t nAddrTon);
  BindBuilder& withAddrNpi(uint8_t nAddrNpi);
  BindBuilder& withAddressRange(const std::string& strAddressRange);
};

}  // namespace smpp::builder

#endif