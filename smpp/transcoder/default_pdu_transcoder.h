#ifndef DEFAULT_PDU_TRANSCODER_H
#define DEFAULT_PDU_TRANSCODER_H

#include "pdu_transcoder.h"
#include "channel_buffer.h"

namespace smpp {

class DefaultPduTranscoder : public PduTranscoder {
 public:
  virtual ChannelBuffer encode(std::unique_ptr<Pdu> ptrPdu) override;
  virtual std::unique_ptr<Pdu> decode(ChannelBuffer strBuffer) override;
};

}  // namespace smpp

#endif