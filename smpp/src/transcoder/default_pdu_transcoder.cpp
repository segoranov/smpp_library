#include "transcoder/default_pdu_transcoder.h"

#include "smppconstants.h"
#include "util/smpp_util.h"

namespace smpp {
void DefaultPduTranscoder::encode(std::shared_ptr<const Pdu> ptrPdu, Buffer& buffer) {
  ptrPdu->writeHeader(buffer);
  ptrPdu->writeBody(buffer);
}

std::unique_ptr<Pdu> DefaultPduTranscoder::decode(Buffer& buffer) {
  auto commandLength = buffer.readInt32();
  auto commandId = buffer.readInt32();
  buffer.resetReadMarker();
  auto pdu = util::createPduByCommandId(commandId);
  pdu->readHeader(buffer);
  pdu->readBody(buffer);
  return pdu;
}

}  // namespace smpp