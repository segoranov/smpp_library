#include "pdu/bind_transceiver.h"

#include "smpp_constants.h"

namespace smpp {

BindTransceiver::BindTransceiver() : BaseBind{constants::CMD_ID_BIND_TRANSCEIVER} {};

void BindTransceiver::serialize(std::ostream& os) const {
  serializeHeader(os);
  serializeBody(os);
}

std::unique_ptr<Pdu> BindTransceiver::createEmpty() {
  return std::unique_ptr<BindTransceiver>{new BindTransceiver{}};
}

std::unique_ptr<Pdu> BindTransceiver::create(uint32_t nCommandLength, std::istream& is) {
  auto bindTransceiverPtr = std::unique_ptr<BindTransceiver>{new BindTransceiver{}};
  bindTransceiverPtr->setCommandLength(nCommandLength);
  bindTransceiverPtr->deserializeAfterCommandId(is);
  return bindTransceiverPtr;
}

}  // namespace smpp