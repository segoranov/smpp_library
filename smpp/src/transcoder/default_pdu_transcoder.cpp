#include "transcoder/default_pdu_transcoder.h"

#include "smppconstants.h"

namespace smpp {

void DefaultPduTranscoder::encode(std::shared_ptr<const Pdu> ptrPdu, Buffer& buffer) {
  buffer.writeInt32(ptrPdu->getCommandLength());
  buffer.writeInt32(ptrPdu->getCommandId());
  buffer.writeInt32(ptrPdu->getCommandStatus());
  buffer.writeInt32(ptrPdu->getSequenceNumber());
  ptrPdu->writeBody(buffer);
}

std::unique_ptr<Pdu> DefaultPduTranscoder::decode(Buffer& buffer) {
  auto commandLength = buffer.readInt32();
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