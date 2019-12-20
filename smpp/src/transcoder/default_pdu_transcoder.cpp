#include "transcoder/default_pdu_transcoder.h"
#include "smppconstants.h"

namespace smpp {

Buffer DefaultPduTranscoder::encode(std::unique_ptr<Pdu> ptrPdu) { 
  Buffer buffer;
  ptrPdu->writeHeader(buffer);
  ptrPdu->writeBody(buffer);
  return {};
} 

std::unique_ptr<Pdu> DefaultPduTranscoder::decode(Buffer& buffer) {
  auto commandLength = buffer.readInt32();
  auto commandId = buffer.readInt32();
  buffer.resetReadMarker();

  


}

}  // namespace smpp