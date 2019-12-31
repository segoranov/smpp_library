#include "pdu/bind_transmitter.h"

#include "smpp_constants.h"

namespace smpp {

BindTransmitter::BindTransmitter() : BaseBind{constants::CMD_ID_BIND_TRANSMITTER} {}

}  // namespace smpp