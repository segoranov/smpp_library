#ifndef CHANNEL_BUFFER_H
#define CHANNEL_BUFFER_H

#include <sstream>
#include <string>

#include "../smppexceptions.h"
#include "../pdu/pdu.h"

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

  void writeByte(char byte);

  void writeInt8(uint8_t nValue);
  void writeInt16(uint16_t nValue);
  void writeInt32(uint32_t nValue);
  void writeBytes(const char *pData, size_t nSize);
  void writeBytes(const std::string &strData);

  // Zero terminated string
  void writeString(const char *szData);
  void writeString(const std::string &str);

  void writeBool(bool bValue);

  char readByte();
  uint8_t readInt8();
  uint16_t readInt16();
  uint32_t readInt32();
  std::string readBytes(size_t nLen);

  // Zero terminated string
  std::string readString();

  bool readBool();

  void resetMarker();

  // sets the values, the offset must be from 0 to length of the encoded message
  void setBytes(const char *pData, size_t nSize, unsigned offset);

  void setInt32(uint32_t nValue, unsigned offset);

  void setInt16(uint16_t nValue, unsigned offset);

  void setInt8(uint8_t nValue, unsigned offset);
};

}

#endif