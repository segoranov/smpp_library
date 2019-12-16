#include "basebind.h"

namespace smpp {

BaseBind::BaseBind(uint32_t nCommandId) : PduRequest{nCommandId} {}

}  // namespace smpp