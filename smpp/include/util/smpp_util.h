#ifndef SMPP_UTIL_H
#define SMPP_UTIL_H

#include <inttypes.h>

#include <cereal/archives/binary.hpp>
#include <sstream>
#include <utility>
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

/**
 * @brief serialize Pdu in compact binary format into a stream
 *
 * For example, we could serialize a PDU of type BindTransmitter into a std::stringstream
 */
template <typename PduType, typename StreamType>
StreamType serializePdu(const PduType& pdu) {
  StreamType ss;
  cereal::BinaryOutputArchive oarchive{ss};
  oarchive(pdu);  // Write the PDU to the stream
  return std::move(ss);
}

}  // namespace smpp::util

#endif
