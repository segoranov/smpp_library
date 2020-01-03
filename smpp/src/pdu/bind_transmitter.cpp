#include "pdu/bind_transmitter.h"

#include "smpp_constants.h"
#include "util/serialization_util.h"

namespace smpp {

BindTransmitter::BindTransmitter() : BaseBind{constants::CMD_ID_BIND_TRANSMITTER} {}

void BindTransmitter::serialize(std::ostream& os) const {
  serializeHeader(os);
  serializeBody(os);
}

std::unique_ptr<BindTransmitter> BindTransmitter::createEmpty() {
  return std::unique_ptr<BindTransmitter>{new BindTransmitter{}};
}

std::unique_ptr<BindTransmitter> BindTransmitter::createPduBody(std::istream& is) {
  auto bindTransmitterPtr = std::unique_ptr<BindTransmitter>{new BindTransmitter{}};
  bindTransmitterPtr->deserializeBody(is);
  return bindTransmitterPtr;
}

}  // namespace smpp