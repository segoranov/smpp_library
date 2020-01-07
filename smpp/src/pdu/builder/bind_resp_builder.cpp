#include "pdu/builder/bind_resp_builder.h"

#include "util/smpp_util.h"

namespace smpp::builder {

BindRespBuilder& BindRespBuilder::withCommandLength(uint32_t nCommandLength) {
  m_optCommandLength = nCommandLength;
  return *this;
}

BindRespBuilder& BindRespBuilder::withCommandStatus(uint32_t nCommandStatus) {
  m_optCommandStatus = nCommandStatus;
  return *this;
}

BindRespBuilder& BindRespBuilder::withSequenceNumber(uint32_t nSequenceNumber) {
  m_optSequenceNumber = nSequenceNumber;
  return *this;
}

BindRespBuilder& BindRespBuilder::withSystemId(const std::string& strSystemId) {
  m_optSystemId = strSystemId;
  return *this;
}

BindRespBuilder& BindRespBuilder::withScInterfaceVersion(uint8_t nScInterfaceVersion) {
  if (!util::isInterfaceVersionValid(nScInterfaceVersion)) {
    std::stringstream error;
    error << "BindRespBuilder: Invalid value for sc_interface_version - [" << nScInterfaceVersion
          << "]";
    throw InvalidInterfaceVersionException{error.str()};
  }

  m_vOptionalTlvParameters.push_back(
      Tlv{constants::TAG_SC_INTERFACE_VERSION, nScInterfaceVersion});

  return *this;
}

}  // namespace smpp::builder