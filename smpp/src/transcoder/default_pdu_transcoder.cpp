#include "../include/transcoder/default_pdu_transcoder.h"

namespace smpp {

Buffer DefaultPduTranscoder::encode(std::unique_ptr<Pdu> ptrPdu) { return Buffer(); }  // TODO SG

std::unique_ptr<Pdu> DefaultPduTranscoder::decode(Buffer strBuffer) {
  return nullptr; // TODO SG
}

}  // namespace smpp