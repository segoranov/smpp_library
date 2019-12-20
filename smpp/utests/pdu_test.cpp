#include "pdu/pdu.h"

#include "buffer/buffer.h"
#include "catch.hpp"
#include "pdu/bindtransmitter.h"

SCENARIO("Pdu header is encoded/decoded properly in buffer", "[pdu_header]") {
  GIVEN("A sample pdu header defined as char array of hex bytes and a buffer") {
    /*
    Sample PDU header (Values are shown in Hex format):
    00 00 00 2F 00 00 00 02 00 00 00 00 00 00 00 01

    The 16-octet header would be decoded as follows:
    00 00 00 2F Command Length 0x0000002F
    00 00 00 02 Command ID 0x00000002
    00 00 00 00 Command Status 0x00000000
    00 00 00 01 Sequence Number 0x00000001
    */
    const char samplePduHeader[] = {0x00, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00, 0x02,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};

    smpp::Buffer buffer;

    WHEN(
        "a pdu is created with the same header and then we encode only the header in the buffer") {
      std::unique_ptr<smpp::Pdu> pdu = std::make_unique<smpp::BindTransmitter>();
      pdu->setCommandLength(47);  // 0x0000002F in hex is 47 in decimal
      pdu->setCommandStatus(0);   // 0x00000000
      pdu->setSequenceNumber(1);  // 0x00000001
      pdu->writeHeader(buffer);

      THEN("the buffer size should be 16") { REQUIRE(buffer.size() == 16); }

      THEN("the buffer as a string should correspond to the sample pdu header") {
        REQUIRE(buffer.toString() == std::string{samplePduHeader, sizeof(samplePduHeader)});
      }

      THEN("the newly created PDU from the buffer should correspond to the first PDU") {
        std::unique_ptr<smpp::Pdu> newPdu = std::make_unique<smpp::BindTransmitter>();
        newPdu->readHeader(buffer);
        REQUIRE(newPdu->getCommandId() == pdu->getCommandId());
        REQUIRE(newPdu->getCommandLength() == pdu->getCommandLength());
        REQUIRE(newPdu->getCommandStatus() == pdu->getCommandStatus());
        REQUIRE(newPdu->getSequenceNumber() == pdu->getSequenceNumber());
      }
    }
  }
}
