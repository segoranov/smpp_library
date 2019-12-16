#include "default_pdu_transcoder.h"

namespace smpp {

ChannelBuffer DefaultPduTranscoder::encode(Pdu pdu) { return ChannelBuffer(); }  // TODO SG

Pdu DefaultPduTranscoder::decode(ChannelBuffer strBuffer) {
  return Pdu(PduHeader{}, true);  // TODO SG
}

}  // namespace smpp