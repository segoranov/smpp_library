#include "transcoder/default_pdu_transcoder.h"

#include "smppconstants.h"
#include "smppexceptions.h"
#include "util/print_util.h"
#include <sstream>

namespace smpp {

Buffer DefaultPduTranscoder::encode(std::shared_ptr<const Pdu> ptrPdu) {
  Buffer buffer;
  buffer.writeInt32(ptrPdu->getCommandLength());
  buffer.writeInt32(ptrPdu->getCommandId());
  buffer.writeInt32(ptrPdu->getCommandStatus());
  buffer.writeInt32(ptrPdu->getSequenceNumber());
  ptrPdu->writeBody(buffer);
  return buffer;
}

std::unique_ptr<Pdu> DefaultPduTranscoder::decode(Buffer& buffer) {
  auto commandLength = buffer.readInt32();

  if (commandLength < constants::PDU_HEADER_LENGTH ) {
    std::stringstream error;
    error << "Invalid PDU length [" << print_util::toHexString(commandLength) << "] parsed";
    throw UnrecoverablePduException(error.str());
  }

  auto commandId = buffer.readInt32();
  auto commandStatus = buffer.readInt32();
  auto sequenceNumber = buffer.readInt32();

  auto pdu = Pdu::createPduByCommandId(commandId);
  pdu->setCommandLength(commandLength);
  pdu->setCommandStatus(commandStatus);
  pdu->setSequenceNumber(sequenceNumber);
  pdu->readBody(buffer);
  return pdu;
}

}  // namespace smpp