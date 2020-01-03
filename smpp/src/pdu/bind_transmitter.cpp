#include "pdu/bind_transmitter.h"

#include "pdu/builder/bind_transmitter_builder.h"
#include "smpp_constants.h"
#include "util/serialization_util.h"

namespace smpp {

BindTransmitter::BindTransmitter() : BaseBind{constants::CMD_ID_BIND_TRANSMITTER} {}

BindTransmitter::BindTransmitter(const builder::BindTransmitterBuilder& params)
    : BaseBind{constants::CMD_ID_BIND_TRANSMITTER} {
  // TODO SG: Throw exceptions here if invalid field exists
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