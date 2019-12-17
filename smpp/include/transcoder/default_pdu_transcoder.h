#ifndef DEFAULT_PDU_TRANSCODER_H
#define DEFAULT_PDU_TRANSCODER_H

#include "pdu_transcoder.h"

namespace smpp {

class DefaultPduTranscoder : public PduTranscoder {
 public:
  virtual Buffer encode(std::unique_ptr<Pdu> ptrPdu) override;
  virtual std::unique_ptr<Pdu> decode(Buffer strBuffer) override;
};

}  // namespace smpp

#endif