#include "util/smpp_util.h"

#include "smppconstants.h"
#include "smppexceptions.h"

namespace smpp::util {

std::unique_ptr<Pdu> createPduByCommandId(uint32_t nCommandId) {
  switch (nCommandId) {
    case constants::CMD_ID_BIND_TRANSMITTER: {
      return std::make_unique<BindTransmitter>();
    }
    default: {
      throw InvalidCommandIdException();
    }
  }
}

}  // namespace smpp::util
