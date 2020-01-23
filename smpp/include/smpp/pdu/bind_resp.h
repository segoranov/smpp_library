#ifndef BIND_RESP_H
#define BIND_RESP_H

#include <string>

#include "smpp/pdu/builder/bind_resp_builder.h"
#include "smpp/pdu/pdu.h"
#include "smpp/util/serialization_util.h"

namespace smpp {
template <uint32_t CommandId>
class BindResp : public Pdu {
  friend const std::unordered_map<uint32_t, Pdu::Factory>& getCommandIdToFactoryMap();

 private:
  std::string m_strSystemId;

 private:
  BindResp();

  static std::unique_ptr<BindResp> create(std::istream& is);

 public:
  explicit BindResp(const builder::BindRespBuilder& params);

  std::string getSystemId() const;

  virtual void serialize(std::ostream& os) const override;
};

template <uint32_t CommandId>
BindResp<CommandId>::BindResp(const builder::BindRespBuilder& params) : Pdu{CommandId} {
  params.checkAllValuesArePresent();

  // TODO SG: Throw exceptions here if invalid field exists
  m_nCommandStatus = params.m_optCommandStatus.value();
  m_nSequenceNumber = params.m_optSequenceNumber.value();
  m_strSystemId = params.m_optSystemId.value();
  m_vOptionalTlvParameters = params.m_vOptionalTlvParameters;

  // Add PDU header to command length
  m_nCommandLength = smpp::constants::PDU_HEADER_LENGTH;

  // Add C-octet strings to command length without forgetting to add 1
  // for the null terminating character
  m_nCommandLength += m_strSystemId.size() + 1;

  // Add optional parameters size to command length
  for (const auto& tlv : m_vOptionalTlvParameters) {
    m_nCommandLength += tlv.size();
  }
}

template <uint32_t CommandId>
std::string BindResp<CommandId>::getSystemId() const {
  return m_strSystemId;
}

template <uint32_t CommandId>
void BindResp<CommandId>::serialize(std::ostream& os) const {
  serializeHeader(os);
  binary::serializeNullTerminatedString(m_strSystemId, os);
  serializeOptionalParameters(os);
}

template <uint32_t CommandId>
BindResp<CommandId>::BindResp() : Pdu{CommandId} {}

template <uint32_t CommandId>
std::unique_ptr<BindResp<CommandId>> BindResp<CommandId>::create(std::istream& is) {
  auto bindRespPtr = std::unique_ptr<BindResp>{new BindResp{}};

  const std::string strSystemId = binary::deserializeNullTerminatedString(is);
  bindRespPtr->m_strSystemId = strSystemId;

  bindRespPtr->deserializeOptionalParameters(is);

  return bindRespPtr;
}

}  // namespace smpp

#endif