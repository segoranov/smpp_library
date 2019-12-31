#include "pdu/bind_receiver.h"
#include "smpp_constants.h"

namespace smpp {

BindReceiver::BindReceiver() : BaseBind{constants::CMD_ID_BIND_RECEIVER} {}

}  // namespace smpp