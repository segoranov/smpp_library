#include "smpp/pdu/outbind.h"

#include "smpp/pdu/builder/outbind_builder.h"
#include "smpp/util/logging.h"
#include "smpp/util/serialization_util.h"

namespace smpp {

Outbind::Outbind() : Pdu{constants::CMD_ID_OUTBIND} {}

Outbind::Outbind(const builder::OutbindBuilder& params) : Pdu{constants::CMD_ID_OUTBIND} {
  m_nCommandStatus = smpp::constants::errors::ESME_ROK;

  params.checkAllValuesArePresent();
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

void Outbind::serialize(std::ostream& os) const {
  serializeHeader(os);
  binary::serializeNullTerminatedString(m_strSystemId, os);
  binary::serializeNullTerminatedString(m_strPassword, os);
}

std::unique_ptr<Outbind> Outbind::create(std::istream& is) {
  INFO << "Outbind::create()";

  auto outbindPtr = std::unique_ptr<Outbind>{new Outbind{}};

  const std::string strSystemId = binary::deserializeNullTerminatedString(is);
  outbindPtr->m_strSystemId = strSystemId;
  DEBUG << "Outbind::create() strSystemId = [" << strSystemId << "]";

  const std::string strPassword = binary::deserializeNullTerminatedString(is);
  outbindPtr->m_strPassword = strPassword;
  DEBUG << "Outbind::create() strPassword = [" << strPassword << "]";

  return outbindPtr;
}

bool Outbind::equals(const Pdu& other) const {
  if (!Pdu::equals(other)) {
    return false;
  }

  auto otherOutbind = static_cast<const Outbind*>(&other);

  return m_strSystemId == otherOutbind->m_strSystemId &&
         m_strPassword == otherOutbind->m_strPassword;
}

}  // namespace smpp