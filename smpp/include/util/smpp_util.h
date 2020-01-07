#ifndef SMPP_UTIL_H
#define SMPP_UTIL_H

#include <inttypes.h>

#include <sstream>
#include <utility>
namespace smpp::util {

/**
 * @brief Check if command length is valid
 */
bool isCommandLengthValid(uint32_t nCommandLength);

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
bool isCommandIdValid(uint32_t nCommandId);

/**
 * @brief Check if interface version is valid
 */
bool isInterfaceVersionValid(uint8_t nInterfaceVersion);

}  // namespace smpp::util

#endif
