#ifndef BIND_H
#define BIND_H

#include <string>

#include "smpp/pdu/builder/bind_builder.h"
#include "smpp/pdu/pdu.h"
#include "smpp/smpp_constants.h"
#include "smpp/util/serialization_util.h"

namespace smpp {

template <uint32_t CommandId>
class Bind;

using BindTransmitter = Bind<constants::CMD_ID_BIND_TRANSMITTER>;
using BindTransceiver = Bind<constants::CMD_ID_BIND_TRANSCEIVER>;
using BindReceiver = Bind<constants::CMD_ID_BIND_RECEIVER>;

template <uint32_t CommandId>
class Bind final : public Pdu {
  friend const std::unordered_map<uint32_t, Pdu::Factory>& getCommandIdToFactoryMap();

 private:
  std::string m_strSystemId;
  std::string m_strPassword;
  std::string m_strSystemType;
  uint8_t m_nInterfaceVersion;
  uint8_t m_nAddrTon;
  uint8_t m_nAddrNpi;
  std::string m_strAddressRange;

 private:
  Bind();

  static std::unique_ptr<Bind<CommandId>> create(std::istream& is);

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
Bind<CommandId>::Bind(const builder::BindBuilder& params) : Pdu{CommandId} {
  if (!params.m_optCommandStatus.has_value())
    throw UndefinedValueException("Bind(): Undefined command status");

  if (!params.m_optSequenceNumber.has_value())
    throw UndefinedValueException("Bind(): Undefined sequence number");

  if (!params.m_optSystemId.has_value())
    throw UndefinedValueException("Bind(): Undefined system id");

  if (!params.m_optPassword.has_value())
    throw UndefinedValueException("Bind(): Undefined password");

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
  m_nCommandStatus = params.m_optCommandStatus.value();
  m_nSequenceNumber = params.m_optSequenceNumber.value();

  m_strSystemId = params.m_optSystemId.value();
  m_strPassword = params.m_optPassword.value();
  m_strSystemType = params.m_optSystemType.value();

  m_nInterfaceVersion = params.m_optInterfaceVersion.value();
  m_nAddrTon = params.m_optAddrTon.value();
  m_nAddrNpi = params.m_optAddrNpi.value();
  m_strAddressRange = params.m_optAddressRange.value();

  // Add PDU header to command length
  m_nCommandLength = smpp::constants::PDU_HEADER_LENGTH;

  // Add C-octet strings to command length without forgetting to add 1
  // for the null terminating character
  m_nCommandLength += m_strSystemId.size() + 1;
  m_nCommandLength += m_strPassword.size() + 1;
  m_nCommandLength += m_strSystemType.size() + 1;
  m_nCommandLength += m_strAddressRange.size() + 1;

  // 3 more mandatory fields with size 1 byte
  m_nCommandLength += 3;

  // No optional parameters for bind operations to add to command length
}

template <uint32_t CommandId>
Bind<CommandId>::Bind() : Pdu{CommandId} {}

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
std::unique_ptr<Bind<CommandId>> Bind<CommandId>::create(std::istream& is) {
  auto bindPtr = std::unique_ptr<Bind<CommandId>>{new Bind<CommandId>{}};

  const std::string strSystemId = binary::deserializeNullTerminatedString(is);
  bindPtr->m_strSystemId = strSystemId;

  const std::string strPassword = binary::deserializeNullTerminatedString(is);
  bindPtr->m_strPassword = strPassword;

  const std::string strSystemType = binary::deserializeNullTerminatedString(is);
  bindPtr->m_strSystemType = strSystemType;

  const uint8_t nInterfaceVersion = binary::deserializeInt8(is);
  bindPtr->m_nInterfaceVersion = nInterfaceVersion;

  const uint8_t nAddrTon = binary::deserializeInt8(is);
  bindPtr->m_nAddrTon = nAddrTon;

  const uint8_t nAddrNpi = binary::deserializeInt8(is);
  bindPtr->m_nAddrNpi = nAddrNpi;

  const std::string strAddressRange = binary::deserializeNullTerminatedString(is);
  bindPtr->m_strAddressRange = strAddressRange;

  return bindPtr;
}

}  // namespace smpp

#endif