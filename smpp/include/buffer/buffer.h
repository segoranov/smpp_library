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

  int size() const { return m_stringBuffer.str().size(); }
  bool isEmpty() const { return size() == 0; }
  void clear() { m_stringBuffer.str(""); }  // empties the buffer

  void writeInt8(uint8_t nValue);
  void writeInt16(uint16_t nValue);
  void writeInt32(uint32_t nValue);
  void writeNullTerminatedString(const char* str);         // C-octet string
  void writeNullTerminatedString(const std::string& str);  // C-octet string
  void writeOctetString(const std::string& str);           // Octet string
  void writeChar(char ch);

  uint8_t readInt8();
  uint16_t readInt16();
  uint32_t readInt32();
  std::string readNullTerminatedString();
  std::string readString(int size);
  char readChar();

  bool areThereMoreBytesToRead() const { return m_stream.eof(); }

  std::string toString() const { return m_stringBuffer.str(); }
  operator std::string() const { return toString(); }

  void resetReadMarker();

  /**
   * Skip bytes when reading from the buffer
   */ 
  void skip(int numberOfBytesToSkip);

  /**
   * @return the number of bytes that are available for reading
   */
  int readableBytes() const;
};

}  // namespace smpp

#endif