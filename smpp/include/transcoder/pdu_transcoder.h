#ifndef PDU_TRANSCODER_H
#define PDU_TRANSCODER_H

#include <memory>
#include <string>

#include "buffer/buffer.h"
#include "pdu/pdu.h"
#include "smppexceptions.h"

namespace smpp {

class PduTranscoder {
 public:
  /**
   * Encodes a PDU into a new buffer.
   * @param pdu The PDU to encode into a buffer
   * @param buffer The buffer to encode the PDU into
   */
  virtual void encode(std::shared_ptr<const Pdu> ptrPdu, Buffer& buffer) = 0;

  /**
   * Decodes a Buffer into a new PDU.
   * @param buffer The buffer to read data from
   * @return The new PDU created from the data
   */
  virtual std::unique_ptr<Pdu> decode(Buffer& buffer) = 0;
};

}  // namespace smpp

#endif