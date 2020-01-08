#ifndef BIND_RESP_H
#define BIND_RESP_H

#include <string>

#include "smpp/pdu/builder/bind_resp_builder.h"
#include "pdu_response.h"
#include "smpp/util/serialization_util.h"

namespace smpp {

template <uint32_t CommandId>
class BindResp;

using BindTransmitterResp = BindResp<constants::CMD_ID_BIND_TRANSMITTER_RESP>;
using BindTransceiverResp = BindResp<constants::CMD_ID_BIND_TRANSCEIVER_RESP>;
using BindReceiverResp = BindResp<constants::CMD_ID_BIND_RECEIVER_RESP>;

template <uint32_t CommandId>
class BindResp : public PduResponse {
  friend const std::unordered_map<uint32_t, Pdu::BodyFactory>& getCommandIdToBodyFactoryMap();

 private:
  std::string m_strSystemId;

 private:
  BindResp();

  virtual void serializeBody(std::ostream& os) const final override;
  virtual void deserializeBody(std::istream& is) final override;
  static std::unique_ptr<BindResp> createPduBody(std::istream& is);

 public:
  explicit BindResp(const builder::BindRespBuilder& params);

  std::string getSystemId() const;

  virtual void serialize(std::ostream& os) const override;
};

template <uint32_t CommandId>
BindResp<CommandId>::BindResp(const builder::BindRespBuilder& params) : PduResponse{CommandId} {
  if (!params.m_optCommandLength.has_value())
    throw UndefinedValueException("BindTransmitterResp(): Undefined command length");

  if (!params.m_optCommandStatus.has_value())
    throw UndefinedValueException("BindTransmitterResp(): Undefined command status");

  if (!params.m_optSequenceNumber.has_value())
    throw UndefinedValueException("BindTransmitterResp(): Undefined sequence number");

  if (!params.m_optSystemId.has_value())
    throw UndefinedValueException("BindTransmitterResp(): Undefined system id");

  // TODO SG: Throw exceptions here if invalid field exists
  m_nCommandLength = params.m_optCommandLength.value();
  m_nCommandStatus = params.m_optCommandStatus.value();
  m_nSequenceNumber = params.m_optSequenceNumber.value();
  m_strSystemId = params.m_optSystemId.value();
  m_vOptionalTlvParameters = params.m_vOptionalTlvParameters;
}

template <uint32_t CommandId>
std::string BindResp<CommandId>::getSystemId() const {
  return m_strSystemId;
}

template <uint32_t CommandId>
void BindResp<CommandId>::serialize(std::ostream& os) const {
  serializeHeader(os);
  serializeBody(os);
}

template <uint32_t CommandId>
BindResp<CommandId>::BindResp() : PduResponse{CommandId} {}

template <uint32_t CommandId>
void BindResp<CommandId>::serializeBody(std::ostream& os) const {
  binary::serializeNullTerminatedString(m_strSystemId, os);
  serializeOptionalParameters(os);
}

template <uint32_t CommandId>
void BindResp<CommandId>::deserializeBody(std::istream& is) {
  const std::string strSystemId = binary::deserializeNullTerminatedString(is);
  m_strSystemId = strSystemId;

  deserializeOptionalParameters(is);
}

template <uint32_t CommandId>
std::unique_ptr<BindResp<CommandId>> BindResp<CommandId>::createPduBody(std::istream& is) {
  auto bindRespPtr = std::unique_ptr<BindResp>{new BindResp{}};
  bindRespPtr->deserializeBody(is);
  return bindRespPtr;
}

}  // namespace smpp

#endif