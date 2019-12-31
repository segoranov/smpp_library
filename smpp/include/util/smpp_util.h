#ifndef SMPP_UTIL_H
#define SMPP_UTIL_H

#include <inttypes.h>

namespace smpp::util {

/**
 * @brief Check if tag is valid
 * @param nTag - the tag to check for validity
 * @return true if the given tag is valid by SMPP specification; false otherwise
 */
bool isTlvTagValid(uint16_t nTag);

/**
 * @brief Check if command id is valid
 * @param nCommandId - the command id to check for validity
 * @return true if the given tag is valid by SMPP specification; false otherwise
 */
bool isCommandIdTagValid(uint32_t nCommandId);

}  // namespace smpp::util

#endif