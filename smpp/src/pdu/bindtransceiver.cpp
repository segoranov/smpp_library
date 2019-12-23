#include "pdu/bindtransceiver.h"
#include "smppconstants.h"

namespace smpp {

BindTransceiver::BindTransceiver() : BaseBind{constants::CMD_ID_BIND_TRANSCEIVER} {}

}  // namespace smpp