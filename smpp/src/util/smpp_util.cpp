#include "util/smpp_util.h"

#include <algorithm>

#include "smpp_constants.h"
#include "smpp_exceptions.h"
namespace smpp::util {

bool isCommandLengthValid(uint32_t nCommandLength) {
  return constants::PDU_HEADER_LENGTH <= nCommandLength &&
         nCommandLength <= constants::PDU_MAX_LENGTH;
}

bool isTlvTagValid(uint16_t nTag) {
  auto it = std::find(constants::ALL_TLV_TAGS.begin(), constants::ALL_TLV_TAGS.end(), nTag);
  return it != constants::ALL_TLV_TAGS.end();
}

bool isCommandIdValid(uint32_t nCommandId) {
  auto it =
      std::find(constants::ALL_COMMAND_IDS.begin(), constants::ALL_COMMAND_IDS.end(), nCommandId);
  return it != constants::ALL_COMMAND_IDS.end();
}

bool isInterfaceVersionValid(uint8_t nInterfaceVersion) {
  return nInterfaceVersion == constants::VERSION_3_3 ||
         nInterfaceVersion == constants::VERSION_3_4 ||
         nInterfaceVersion == constants::VERSION_5_0;
}

}  // namespace smpp::util
