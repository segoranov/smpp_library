#include "default_pdu_transcoder.h"

namespace smpp {

ChannelBuffer DefaultPduTranscoder::encode(std::unique_ptr<Pdu> ptrPdu) { return ChannelBuffer(); }  // TODO SG

std::unique_ptr<Pdu> DefaultPduTranscoder::decode(ChannelBuffer strBuffer) {
  return nullptr; // TODO SG
}

}  // namespace smpp