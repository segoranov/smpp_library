#ifndef BIND_TRANSMITTER_RESP_BUILDER_H
#define BIND_TRANSMITTER_RESP_BUILDER_H

#include <optional>
#include <string>
#include <vector>

#include "pdu/bind_transmitter_resp.h"
#include "pdu/pdu.h"
#include "tlv/tlv.h"

namespace smpp::builder {

/**
 * Class used for creation of bind_transmitter_resp PDUs in a more readable and reliable way.
 * Forces all objects to have their fields defined.
 *
 * The named parameter idiom is used
 * - https://isocpp.org/wiki/faq/ctors#named-parameter-idiom
 * - https://stackoverflow.com/questions/40264/how-many-constructor-arguments-is-too-many
 */
class BindTransmitterRespBuilder {
 private:
  friend class smpp::BindTransmitterResp;

  std::optional<uint32_t> m_optCommandLength;
  std::optional<uint32_t> m_optCommandStatus;
  std::optional<uint32_t> m_optSequenceNumber;
  std::optional<std::string> m_optSystemId;
  std::vector<Tlv> m_vOptionalTlvParameters;

 public:
  BindTransmitterRespBuilder() = default;

  BindTransmitterRespBuilder& withCommandLength(uint32_t nCommandLength);
  BindTransmitterRespBuilder& withCommandStatus(uint32_t nCommandStatus);
  BindTransmitterRespBuilder& withSequenceNumber(uint32_t nSequenceNumber);
  BindTransmitterRespBuilder& withSystemId(const std::string& strSystemId);
  BindTransmitterRespBuilder& withOptionalParameter(const smpp::Tlv& tlv);
};

}  // namespace smpp::builder

#endif