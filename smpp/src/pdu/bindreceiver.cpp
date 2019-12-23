#include "pdu/bindreceiver.h"
#include "smppconstants.h"

namespace smpp {

BindReceiver::BindReceiver() : BaseBind{constants::CMD_ID_BIND_RECEIVER} {}

}  // namespace smpp