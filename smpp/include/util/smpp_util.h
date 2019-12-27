#ifndef SMPP_UTIL_H
#define SMPP_UTIL_H

#include <inttypes.h>

namespace smpp::util {

/**
 * @param nTag - the tag to check for validity
 * @return true if the given tag is valid by SMPP specification; false otherwise
 */
bool isTlvTagValid(uint16_t nTag);

}  // namespace smpp::util

#endif