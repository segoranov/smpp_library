#include "pdu/bindtransmitter.h"

#include "smppconstants.h"

namespace smpp {

BindTransmitter::BindTransmitter() : BaseBind{constants::CMD_ID_BIND_TRANSMITTER} {}

}  // namespace smpp