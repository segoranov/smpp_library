#ifndef BUFFER_H
#define BUFFER_H

#include <sstream>
#include <string>

#include "smppexceptions.h"

namespace smpp {

/**
 *  Class used for binary serializing/deserializing of PDUs. Contains raw binary data.
 */
class Buffer {
 private:
  std::stringbuf m_stringBuffer;
  std::iostream m_stream;

 public:
  Buffer();
  Buffer(const Buffer& other);

  /**
   * Write raw data to buffer
   */
  void writeInt8(uint8_t nValue);
  void writeInt16(uint16_t nValue);
  void writeInt32(uint32_t nValue);
  void writeNullTerminatedString(const char* str);         // C-octet string
  void writeNullTerminatedString(const std::string& str);  // C-octet string
  void writeOctetString(const std::string& str);
  void writeChar(char ch);

  /**
   * Read raw data from buffer
   */
  uint8_t readInt8();
  uint16_t readInt16();
  uint32_t readInt32();
  std::string readNullTerminatedString();
  std::string readOctetString(int size);
  char readChar();

  /**
   * Utility methods
   */

  bool areThereBytesToRead();

  /**
   * @return the size of the buffer
   */
  int size() const;

  /**
   * @return true if the buffer is empty; false otherwise
   */
  bool isEmpty() const;

  /**
   * @brief Empties the buffer
   */
  void clear();

  /**
   * @brief reset reading marker by putting it to the beginning of the buffer
   */
  void resetReadMarker();

  /**
   * @brief Skip bytes when reading from the buffer
   * @param nNumberOfBytesToSkip - how many bytes forward to move the reading marker
   */
  void skip(int nNumberOfBytesToSkip);

  std::string toString() const;
  operator std::string() const;
};

}  // namespace smpp

#endif