#include "util/smpp_util.h"

#include <algorithm>

#include "smppconstants.h"
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

}  // namespace smpp::util
