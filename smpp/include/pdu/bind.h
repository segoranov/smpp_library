#ifndef BIND_H
#define BIND_H

#include <string>

#include "pdu/builder/bind_builder.h"
#include "pdu_request.h"
#include "smpp_constants.h"
#include "util/serialization_util.h"

namespace smpp {

template <uint32_t CommandId>
class Bind;

using BindTransmitter = Bind<constants::CMD_ID_BIND_TRANSMITTER>;
using BindTransceiver = Bind<constants::CMD_ID_BIND_TRANSCEIVER>;
using BindReceiver = Bind<constants::CMD_ID_BIND_RECEIVER>;

template <uint32_t CommandId>
class Bind final : public PduRequest {
  friend const std::unordered_map<uint32_t, Pdu::BodyFactory>& getCommandIdToBodyFactoryMap();

 private:
  std::string m_strSystemId;
  std::string m_strPassword;
  std::string m_strSystemType;
  uint8_t m_nInterfaceVersion;
  uint8_t m_nAddrTon;
  uint8_t m_nAddrNpi;
  std::string m_strAddressRange;

 private:
  Bind() : PduRequest{CommandId} {}

  virtual void serializeBody(std::ostream& os) const final override;
  virtual void deserializeBody(std::istream& is) final override;

  static std::unique_ptr<Bind<CommandId>> createPduBody(std::istream& is);

 public:
  explicit Bind(const builder::BindBuilder& params);

  std::string getSystemId() const;
  std::string getPassword() const;
  std::string getSystemType() const;
  uint8_t getInterfaceVersion() const;
  uint8_t getAddrTon() const;
  uint8_t getAddrNpi() const;
  std::string getAddressRange() const;

  virtual void serialize(std::ostream& os) const override;
};

template <uint32_t CommandId>
Bind<CommandId>::Bind(const builder::BindBuilder& params) : PduRequest{CommandId} {
  if (!params.m_optCommandLength.has_value())
    throw UndefinedValueException("Bind(): Undefined command length");

  if (!params.m_optCommandStatus.has_value())
    throw UndefinedValueException("Bind(): Undefined command status");

  if (!params.m_optSequenceNumber.has_value())
    throw UndefinedValueException("Bind(): Undefined sequence number");

  if (!params.m_optSystemId.has_value())
    throw UndefinedValueException("Bind(): Undefined system id");

  if (!params.m_optSystemType.has_value())
    throw UndefinedValueException("Bind(): Undefined system type");

  if (!params.m_optInterfaceVersion.has_value())
    throw UndefinedValueException("Bind(): Undefined interface version");

  if (!params.m_optAddrTon.has_value())
    throw UndefinedValueException("Bind(): Undefined addr ton");

  if (!params.m_optAddrNpi.has_value())
    throw UndefinedValueException("Bind(): Undefined addr npi");

  if (!params.m_optAddressRange.has_value())
    throw UndefinedValueException("Bind(): Undefined address range");

  // TODO SG: Validation
  m_nCommandLength = params.m_optCommandLength.value();
  m_nCommandStatus = params.m_optCommandStatus.value();
  m_nSequenceNumber = params.m_optSequenceNumber.value();

  m_strSystemId = params.m_optSystemId.value();
  m_strPassword = params.m_optPassword.value();
  m_strSystemType = params.m_optSystemType.value();

  m_nInterfaceVersion = params.m_optInterfaceVersion.value();
  m_nAddrTon = params.m_optAddrTon.value();
  m_nAddrNpi = params.m_optAddrNpi.value();
  m_strAddressRange = params.m_optAddressRange.value();
}

template <uint32_t CommandId>
std::string Bind<CommandId>::getSystemId() const {
  return m_strSystemId;
}

template <uint32_t CommandId>
std::string Bind<CommandId>::getPassword() const {
  return m_strPassword;
}

template <uint32_t CommandId>
std::string Bind<CommandId>::getSystemType() const {
  return m_strSystemType;
}

template <uint32_t CommandId>
uint8_t Bind<CommandId>::getInterfaceVersion() const {
  return m_nInterfaceVersion;
}

template <uint32_t CommandId>
uint8_t Bind<CommandId>::getAddrTon() const {
  return m_nAddrTon;
}

template <uint32_t CommandId>
uint8_t Bind<CommandId>::getAddrNpi() const {
  return m_nAddrNpi;
}

template <uint32_t CommandId>
std::string Bind<CommandId>::getAddressRange() const {
  return m_strAddressRange;
}

template <uint32_t CommandId>
void Bind<CommandId>::serialize(std::ostream& os) const {
  serializeHeader(os);
  serializeBody(os);
}

template <uint32_t CommandId>
void Bind<CommandId>::serializeBody(std::ostream& os) const {
  binary::serializeNullTerminatedString(m_strSystemId, os);
  binary::serializeNullTerminatedString(m_strPassword, os);
  binary::serializeNullTerminatedString(m_strSystemType, os);
  binary::serializeInt8(m_nInterfaceVersion, os);
  binary::serializeInt8(m_nAddrTon, os);
  binary::serializeInt8(m_nAddrNpi, os);
  binary::serializeNullTerminatedString(m_strAddressRange, os);
  serializeOptionalParameters(os);  // optional parameters are part of the body
}

template <uint32_t CommandId>
void Bind<CommandId>::deserializeBody(std::istream& is) {
  const std::string strSystemId = binary::deserializeNullTerminatedString(is);
  m_strSystemId = strSystemId;

  const std::string strPassword = binary::deserializeNullTerminatedString(is);
  m_strPassword = strPassword;

  const std::string strSystemType = binary::deserializeNullTerminatedString(is);
  m_strSystemType = strSystemType;

  const uint8_t nInterfaceVersion = binary::deserializeInt8(is);
  m_nInterfaceVersion = nInterfaceVersion;

  const uint8_t nAddrTon = binary::deserializeInt8(is);
  m_nAddrTon = nAddrTon;

  const uint8_t nAddrNpi = binary::deserializeInt8(is);
  m_nAddrNpi = nAddrNpi;

  const std::string strAddressRange = binary::deserializeNullTerminatedString(is);
  m_strAddressRange = strAddressRange;
}

template <uint32_t CommandId>
std::unique_ptr<Bind<CommandId>> Bind<CommandId>::createPduBody(std::istream& is) {
  auto bindPtr = std::unique_ptr<Bind<CommandId>>{new Bind<CommandId>{}};
  bindPtr->deserializeBody(is);
  return bindPtr;
}

}  // namespace smpp

#endif