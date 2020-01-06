#ifndef BIND_TRANSMITTER_BUILDER_H
#define BIND_TRANSMITTER_BUILDER_H

#include <optional>
#include <string>
#include <vector>

#include "pdu/bind_transmitter.h"
#include "pdu/pdu.h"
#include "tlv/tlv.h"

namespace smpp::builder {

/**
 * Class used for creation of bind_transmitter PDUs in a more readable and reliable way.
 * Forces all objects to have their fields defined.
 *
 * The named parameter idiom is used
 * - https://isocpp.org/wiki/faq/ctors#named-parameter-idiom
 * - https://stackoverflow.com/questions/40264/how-many-constructor-arguments-is-too-many
 */
class BindTransmitterBuilder {
 private:
  friend class smpp::BindTransmitter;

  std::optional<uint32_t> m_optCommandLength;
  uint32_t m_nCommandId;
  std::optional<uint32_t> m_optCommandStatus;
  std::optional<uint32_t> m_optSequenceNumber;

  std::optional<std::string> m_optSystemId;
  std::optional<std::string> m_optPassword;
  std::optional<std::string> m_optSystemType;
  std::optional<uint8_t> m_optInterfaceVersion;
  std::optional<uint8_t> m_optAddrTon;
  std::optional<uint8_t> m_optAddrNpi;
  std::optional<std::string> m_optAddressRange;

 public:
  BindTransmitterBuilder();

  BindTransmitterBuilder& withCommandLength(uint32_t nCommandLength);
  BindTransmitterBuilder& withCommandStatus(uint32_t nCommandStatus);
  BindTransmitterBuilder& withSequenceNumber(uint32_t nSequenceNumber);
  BindTransmitterBuilder& withSystemId(const std::string& strSystemId);
  BindTransmitterBuilder& withPassword(const std::string& strPassword);
  BindTransmitterBuilder& withSystemType(const std::string& strSystemType);
  BindTransmitterBuilder& withInterfaceVersion(uint8_t nInterfaceVersion);
  BindTransmitterBuilder& withAddrTon(uint8_t nAddrTon);
  BindTransmitterBuilder& withAddrNpi(uint8_t nAddrNpi);
  BindTransmitterBuilder& withAddressRange(const std::string& strAddressRange);
};

}  // namespace smpp::builder

#endif