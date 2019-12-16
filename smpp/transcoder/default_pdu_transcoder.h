#ifndef DEFAULT_PDU_TRANSCODER_H
#define DEFAULT_PDU_TRANSCODER_H

#include "pdu_transcoder.h"
#include "channel_buffer.h"

namespace smpp {

class DefaultPduTranscoder : public PduTranscoder {
 public:
  virtual ChannelBuffer encode(Pdu pdu) override;
  virtual Pdu decode(ChannelBuffer strBuffer) override;
};

}  // namespace smpp

#endif