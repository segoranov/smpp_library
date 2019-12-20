#ifndef DEFAULT_PDU_TRANSCODER_H
#define DEFAULT_PDU_TRANSCODER_H

#include "pdu_transcoder.h"

namespace smpp {

class DefaultPduTranscoder : public PduTranscoder {
 public:
  virtual void encode(std::shared_ptr<const Pdu> ptrPdu, Buffer& buffer) override;
  virtual std::unique_ptr<Pdu> decode(Buffer& buffer) override;
};

}  // namespace smpp

#endif