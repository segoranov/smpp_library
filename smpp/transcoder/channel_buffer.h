#ifndef CHANNEL_BUFFER_H
#define CHANNEL_BUFFER_H

#include <sstream>
#include <string>

#include "../pdu/pdu.h"
#include "../smppexceptions.h"

/**
 *  Class used for encoding/decoding of PDUs.
 */
namespace smpp {

class ChannelBuffer {
 private:
  std::stringbuf m_stringBuffer;
  std::iostream m_stream;

 public:
  ChannelBuffer();

  int size() const { return m_stringBuffer.str().size(); }
  bool isEmpty() const { return size() == 0; }
  void clear() { m_stringBuffer.str(""); } // empties the buffer

  ChannelBuffer& operator<<(uint8_t nValue);
  ChannelBuffer& operator<<(uint16_t nValue);
  ChannelBuffer& operator<<(uint32_t nValue);
  ChannelBuffer& operator<<(const char* str);
  ChannelBuffer& operator<<(const std::string& str);

  void writeInt8(uint8_t nValue);
  void writeInt16(uint16_t nValue);
  void writeInt32(uint32_t nValue);
  void writeNullTerminatedString(const char* str);  // C-octet string
  void writeString(const std::string& str);         // Octet string
  void writeChar(char ch);

  uint8_t readInt8();
  uint16_t readInt16();
  uint32_t readInt32();
  std::string readNullTerminatedString();
  std::string readString(int size);
  char readChar();

  void resetMarker();

  // sets the values, the offset must be from 0 to length of the encoded message
  void setBytes(const char* pData, size_t nSize, unsigned offset);

  void setInt32(uint32_t nValue, unsigned offset);

  void setInt16(uint16_t nValue, unsigned offset);

  void setInt8(uint8_t nValue, unsigned offset);
};

}  // namespace smpp

#endif