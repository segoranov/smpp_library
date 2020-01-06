#include "pdu/bind_transmitter.h"

#include "pdu/builder/bind_transmitter_builder.h"
#include "smpp_constants.h"
#include "util/serialization_util.h"

namespace smpp {

BindTransmitter::BindTransmitter() : BaseBind{constants::CMD_ID_BIND_TRANSMITTER} {}

BindTransmitter::BindTransmitter(const builder::BindTransmitterBuilder& params)
    : BaseBind{constants::CMD_ID_BIND_TRANSMITTER} {
  if (!params.m_optCommandLength)
    throw UndefinedValueException("BindTransmitter(): Undefined command length");

  if (!params.m_optCommandStatus)
    throw UndefinedValueException("BindTransmitter(): Undefined command status");

  if (!params.m_optSequenceNumber)
    throw UndefinedValueException("BindTransmitter(): Undefined sequence number");

  if (!params.m_optSystemId)
    throw UndefinedValueException("BindTransmitter(): Undefined system id");

  if (!params.m_optSystemType)
    throw UndefinedValueException("BindTransmitter(): Undefined system type");

  if (!params.m_optInterfaceVersion)
    throw UndefinedValueException("BindTransmitter(): Undefined interface version");

  if (!params.m_optAddrTon) throw UndefinedValueException("BindTransmitter(): Undefined addr ton");

  if (!params.m_optAddrNpi) throw UndefinedValueException("BindTransmitter(): Undefined addr npi");

  if (!params.m_optAddressRange)
    throw UndefinedValueException("BindTransmitter(): Undefined address range");

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
}  // namespace smpp

void BindTransmitter::serialize(std::ostream& os) const {
  serializeHeader(os);
  serializeBody(os);
}

std::unique_ptr<BindTransmitter> BindTransmitter::createPduBody(std::istream& is) {
  auto bindTransmitterPtr = std::unique_ptr<BindTransmitter>{new BindTransmitter{}};
  bindTransmitterPtr->deserializeBody(is);
  return bindTransmitterPtr;
}

}  // namespace smpp