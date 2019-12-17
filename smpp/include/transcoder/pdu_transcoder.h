#ifndef PDU_TRANSCODER_H
#define PDU_TRANSCODER_H

#include <memory>
#include <string>

#include "pdu/pdu.h"
#include "smppexceptions.h"
#include "buffer/buffer.h"

namespace smpp {

class PduTranscoder {
 public:
  // TODO: Throw proper exceptions

  /**
   * Encodes a PDU into a new buffer.
   * @param pdu The PDU to convert into a buffer
   * @return The new buffer ready to send on a Channel
   * @throws UnrecoverablePduEncodingException Thrown if there is an unrecoverable
   *      error while encoding the buffer.  Recommended action is to rebind
   *      the session.
   * @throws RecoverablePduEncodingException Thrown if there is recoverable
   *      error while encoding the buffer. A good example is an optional parameter
   *      that is invalid or a terminating null byte wasn't found.
   */
  virtual Buffer encode(
      std::unique_ptr<Pdu> ptrPdu) = 0;  // throw UnrecoverablePduException, RecoverablePduException;

  /**
   * Decodes a Buffer into a new PDU.
   * @param buffer The buffer to read data from
   * @return The new PDU created from the data
   * @throws UnrecoverablePduEncodingException Thrown if there is an unrecoverable
   *      error while decoding the buffer.  Recommended action is to rebind
   *      the session.
   * @throws RecoverablePduEncodingException Thrown if there is recoverable
   *      error while decoding the buffer. A good example is an optional parameter
   *      that is invalid or a terminating null byte wasn't found.
   */
  virtual std::unique_ptr<Pdu> decode(
      Buffer strBuffer) = 0;  // throws UnrecoverablePduException, RecoverablePduException;
};

}  // namespace smpp

#endif