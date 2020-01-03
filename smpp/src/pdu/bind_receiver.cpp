#include "pdu/bind_receiver.h"

#include "smpp_constants.h"

namespace smpp {

BindReceiver::BindReceiver() : BaseBind{constants::CMD_ID_BIND_RECEIVER} {}

void BindReceiver::serialize(std::ostream& os) const {
  serializeHeader(os);
  serializeBody(os);
}

std::unique_ptr<BindReceiver> BindReceiver::createEmpty() {
  return std::unique_ptr<BindReceiver>{new BindReceiver{}};
}

std::unique_ptr<BindReceiver> BindReceiver::createPduBody(std::istream& is) {
  auto bindReceiverPtr = std::unique_ptr<BindReceiver>{new BindReceiver{}};
  bindReceiverPtr->deserializeBody(is);
  return bindReceiverPtr;
}

}  // namespace smpp