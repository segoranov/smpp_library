#include "pdu/base_bind_resp.h"

#include "smpp_constants.h"
#include "util/serialization_util.h"

namespace smpp {

BaseBindResp::BaseBindResp(uint32_t nCommandId) : PduResponse{nCommandId} {}

std::string BaseBindResp::getSystemId() const { return m_strSystemId; }

void BaseBindResp::serializeBody(std::ostream& os) const {
  binary::serializeNullTerminatedString(m_strSystemId, os);
  serializeOptionalParameters(os);
}

void BaseBindResp::deserializeBody(std::istream& is) {
  const std::string strSystemId = binary::deserializeNullTerminatedString(is);
  m_strSystemId = strSystemId;

  // TODO SG: Error handling and check for correctnes of tag...
  if (!is.eof()) {
    Tlv sc_interface_version;
    sc_interface_version.deserialize(is);

    if (!sc_interface_version.getTag() == constants::TAG_SC_INTERFACE_VERSION) {
      throw InvalidTagException{
          "Tag different than 'sc_interface_version' detected during deserialization of "
          "BaseBindResp"};
    }

    m_vOptionalTlvParameters.push_back(sc_interface_version);
  }
}

}  // namespace smpp