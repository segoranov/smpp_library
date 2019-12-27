#include "util/smpp_util.h"

#include <algorithm>

#include "smppconstants.h"
namespace smpp::util {

bool isTlvTagValid(uint16_t nTag) {
  auto it = std::find(constants::ALL_TLV_TAGS.begin(), constants::ALL_TLV_TAGS.end(), nTag);
  return it != constants::ALL_TLV_TAGS.end();
}

}  // namespace smpp::util
