#ifndef BIND_RESP_H
#define BIND_RESP_H

#include <string>

#include "pdu/builder/bind_resp_builder.h"
#include "pdu_response.h"
#include "util/serialization_util.h"

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
  BindResp() : PduResponse{CommandId} {}

  std::string m_strSystemId;

 private:
  virtual void serializeBody(std::ostream& os) const final override {
    binary::serializeNullTerminatedString(m_strSystemId, os);
    serializeOptionalParameters(os);
  }

  virtual void deserializeBody(std::istream& is) final override {
    const std::string strSystemId = binary::deserializeNullTerminatedString(is);
    m_strSystemId = strSystemId;

    deserializeOptionalParameters(is);
  }

  static std::unique_ptr<BindResp> createPduBody(std::istream& is) {
    auto bindRespPtr = std::unique_ptr<BindResp>{new BindResp{}};
    bindRespPtr->deserializeBody(is);
    return bindRespPtr;
  }

 public:
  explicit BindResp(const builder::BindRespBuilder& params) : PduResponse{CommandId} {
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

  std::string getSystemId() const { return m_strSystemId; }

  virtual void serialize(std::ostream& os) const override {
    serializeHeader(os);
    serializeBody(os);
  }
};

}  // namespace smpp

#endif