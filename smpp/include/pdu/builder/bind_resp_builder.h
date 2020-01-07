#ifndef BIND_RESP_BUILDER_H
#define BIND_RESP_BUILDER_H

#include <optional>
#include <string>
#include <vector>

#include "pdu/pdu.h"
#include "tlv/tlv.h"

namespace smpp {

template <uint32_t CommandId>
class BindResp;

}  // namespace smpp

namespace smpp::builder {

/**
 * Class used for creation of bind_resp PDUs in a more readable and reliable way.
 * - bind_transmitter_resp
 * - bind transceiver_resp
 * - bind_transceiver_resp
 *
 * The named parameter idiom is used
 * - https://isocpp.org/wiki/faq/ctors#named-parameter-idiom
 * - https://stackoverflow.com/questions/40264/how-many-constructor-arguments-is-too-many
 */
class BindRespBuilder {
 private:
  template <uint32_t CommandId>
  friend class smpp::BindResp;

  std::optional<uint32_t> m_optCommandLength;
  std::optional<uint32_t> m_optCommandStatus;
  std::optional<uint32_t> m_optSequenceNumber;
  std::optional<std::string> m_optSystemId;
  std::vector<Tlv> m_vOptionalTlvParameters;

 public:
  BindRespBuilder() = default;

  BindRespBuilder& withCommandLength(uint32_t nCommandLength);
  BindRespBuilder& withCommandStatus(uint32_t nCommandStatus);
  BindRespBuilder& withSequenceNumber(uint32_t nSequenceNumber);
  BindRespBuilder& withSystemId(const std::string& strSystemId);

  /**
   * Bind responses support only 1 optional TLV parameter:
   * sc_interface_version
   */
  BindRespBuilder& withScInterfaceVersion(uint8_t nScInterfaceVersion);
};

}  // namespace smpp::builder

#endif