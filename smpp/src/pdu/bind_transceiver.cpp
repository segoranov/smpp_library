#include "pdu/bind_transceiver.h"
#include "smpp_constants.h"

namespace smpp {

BindTransceiver::BindTransceiver() : BaseBind{constants::CMD_ID_BIND_TRANSCEIVER} {}

}  // namespace smpp