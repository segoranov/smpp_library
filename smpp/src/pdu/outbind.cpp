#include "smpp/pdu/outbind.h"

#include "smpp/pdu/builder/outbind_builder.h"
#include "smpp/util/logging.h"
#include "smpp/util/serialization_util.h"

namespace smpp {

Outbind::Outbind() : PduRequest{constants::CMD_ID_OUTBIND} {}

Outbind::Outbind(const builder::OutbindBuilder& params) : PduRequest{constants::CMD_ID_OUTBIND} {
  if (!params.m_optCommandStatus.has_value()) {
    throw UndefinedValueException("Outbind(): Undefined command status");
  }

  if (!params.m_optSequenceNumber.has_value()) {
    throw UndefinedValueException("Outbind(): Undefined sequence number");
  }

  if (!params.m_optSystemId.has_value())
    throw UndefinedValueException("Outbind(): Undefined system id");

  if (!params.m_optPassword.has_value())
    throw UndefinedValueException("Outbind(): Undefined password");

  m_nCommandStatus = params.m_optCommandStatus.value();
  m_nSequenceNumber = params.m_optSequenceNumber.value();
  m_strSystemId = params.m_optSystemId.value();
  m_strPassword = params.m_optPassword.value();

  // Add PDU header to command length
  m_nCommandLength = smpp::constants::PDU_HEADER_LENGTH;

  // Add C-octet strings to command length without forgetting to add 1
  // for the null terminating character
  m_nCommandLength += m_strSystemId.size() + 1;
  m_nCommandLength += m_strPassword.size() + 1;

  // No optional parameters for outbind
}

std::string Outbind::getSystemId() const { return m_strSystemId; }

std::string Outbind::getPassword() const { return m_strPassword; }

void Outbind::serializeBody(std::ostream& os) const {
  binary::serializeNullTerminatedString(m_strSystemId, os);
  binary::serializeNullTerminatedString(m_strPassword, os);
}

void Outbind::deserializeBody(std::istream& is) {
  INFO << "Outbind::deserializeBody()";

  const std::string strSystemId = binary::deserializeNullTerminatedString(is);
  m_strSystemId = strSystemId;
  DEBUG << "Outbind::deserializeBody() strSystemId = [" << strSystemId << "]";

  const std::string strPassword = binary::deserializeNullTerminatedString(is);
  m_strPassword = strPassword;
  DEBUG << "Outbind::deserializeBody() strPassword = [" << strPassword << "]";
}

void Outbind::serialize(std::ostream& os) const {
  serializeHeader(os);
  serializeBody(os);
}

std::unique_ptr<Outbind> Outbind::createPduBody(std::istream& is) {
  auto OutbindPtr = std::unique_ptr<Outbind>{new Outbind{}};
  OutbindPtr->deserializeBody(is);
  return OutbindPtr;
}

}  // namespace smpp