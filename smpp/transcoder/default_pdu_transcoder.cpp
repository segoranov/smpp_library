#include "default_pdu_transcoder.h"

namespace smpp {

ChannelBuffer DefaultPduTranscoder::encode(Pdu pdu) {
    return ChannelBuffer();
}

Pdu DefaultPduTranscoder::decode(ChannelBuffer strBuffer) {
    return Pdu();
}

}