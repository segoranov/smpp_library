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
 * @brief serialize Pdu into a stream in compact binary format
 *
 * For example, we could serialize a PDU of type BindTransmitter into a std::stringstream
 */
template <typename PduType, typename StreamType>
StreamType serializePdu(const PduType& pdu) {
  StreamType stream;
  cereal::BinaryOutputArchive oarchive{stream};
  oarchive(pdu);  // Write the PDU to the stream
  return stream;
}

/**
 * @brief deserialize Pdu from stream with raw binary data into an object
 *
 * For example, we could deserialize a PDU of type BindTransmitter from a std::stringstream
 */
template <typename PduType, typename StreamType>
PduType deserializePdu(StreamType& stream) {
  PduType deserializedPdu;
  cereal::BinaryInputArchive iarchive{stream};
  iarchive(deserializedPdu);  // Read the data from the archive into the PDU
  return deserializedPdu;
}

}  // namespace smpp::util

#endif
