#include "pdu/pdu.h"

#include "buffer/buffer.h"
#include "catch.hpp"
#include "pdu/bindtransmitter.h"
#include "smppconstants.h"
#include "transcoder/default_pdu_transcoder.h"
#include "util/smpp_util.h"

SCENARIO("Pdu header is encoded/decoded properly in buffer", "[pdu_header]") {
  GIVEN("A sample bindtransmitter pdu defined as raw data (array of hex bytes)") {
    /*
    Sample PDU (Values are shown in Hex format):
    00 00 00 2F 00 00 00 02 00 00 00 00 00 00 00 01
    53 4D 50 50 33 54 45 53 54 00 73 65 63 72 65 74
    30 38 00 53 55 42 4D 49 54 31 00 50 01 01 00

    The 16-octet header would be decoded as follows:
    00 00 00 2F Command Length 0x0000002F
    00 00 00 02 Command ID 0x00000002
    00 00 00 00 Command Status 0x00000000
    00 00 00 01 Sequence Number 0x00000001

    The remaining data represents the PDU body (which in this example relates to the
    bind_transmitter PDU).
    This is diagnosed as follows:
    53 4D 50 50 33 54 45 53 54 00       system_id (“SMPP3TEST”)
    73 65 63 72 65 74 30 38 00          password (“secret08”)
    53 55 42 4D 49 54 31 00             system_type (“SUBMIT1”)
    50                                  interface_version (0x50 “V5.0 compliant”)
    01                                  addr_ton (0x01)
    01                                  addr_npi (0x01)
    00                                  addr_range (NULL)
    */

    const char samplePdu[] = {0x00, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00,
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x53, 0x4D, 0x50, 0x50,
                              0x33, 0x54, 0x45, 0x53, 0x54, 0x00, 0x73, 0x65, 0x63, 0x72,
                              0x65, 0x74, 0x30, 0x38, 0x00, 0x53, 0x55, 0x42, 0x4D, 0x49,
                              0x54, 0x31, 0x00, 0x50, 0x01, 0x01, 0x00};

    THEN("The size of the sample pdu should be 47") { REQUIRE(sizeof(samplePdu) == 47); }

    AND_GIVEN("a buffer") {
      smpp::Buffer buffer;

      AND_GIVEN("a sample BindTransmitter PDU corresponding to the raw PDU") {
        std::shared_ptr<smpp::Pdu> pdu =
            smpp::util::createPduByCommandId(smpp::constants::CMD_ID_BIND_TRANSMITTER);
        pdu->setCommandLength(47);  // 0x0000002F in hex is 47 in decimal
        pdu->setCommandStatus(0);   // 0x00000000
        pdu->setSequenceNumber(1);  // 0x00000001

        auto baseBind = dynamic_cast<smpp::BaseBind*>(pdu.get());
        baseBind->setSystemId("SMPP3TEST");
        baseBind->setPassword("secret08");
        baseBind->setSystemType("SUBMIT1");
        baseBind->setInterfaceVersion(0x50);
        smpp::Address address{0x01, 0x01};
        baseBind->setAddress(address);

        AND_GIVEN("a DefaultPduTranscoder") {
          std::unique_ptr<smpp::PduTranscoder> pduTranscoder =
              std::make_unique<smpp::DefaultPduTranscoder>();

          WHEN("the BindTransmitter PDU is written to the buffer by using the transcoder") {
            pduTranscoder->encode(pdu, buffer);

            THEN(
                "the buffer size should be equal to the command length of the BindTransmitter "
                "PDU") {
              REQUIRE(buffer.size() == pdu->getCommandLength());
            }

            THEN("the buffer as a string should correspond to the sample pdu header") {
              REQUIRE(buffer.toString() == std::string{samplePdu, sizeof(samplePdu)});
            }

            THEN(
                "the newly created PDU from the buffer should correspond to the first "
                "BindTransmitter PDU") {
              auto decodedPdu = pduTranscoder->decode(buffer);
              REQUIRE(decodedPdu->getCommandId() == pdu->getCommandId());
              REQUIRE(decodedPdu->getCommandLength() == pdu->getCommandLength());
              REQUIRE(decodedPdu->getCommandStatus() == pdu->getCommandStatus());
              REQUIRE(decodedPdu->getSequenceNumber() == pdu->getSequenceNumber());

              auto decodedBaseBind = dynamic_cast<smpp::BaseBind*>(decodedPdu.get());
              REQUIRE(decodedBaseBind->getSystemId() == baseBind->getSystemId());
              REQUIRE(decodedBaseBind->getPassword() == baseBind->getPassword());
              REQUIRE(decodedBaseBind->getSystemType() == baseBind->getSystemType());
              REQUIRE(decodedBaseBind->getAddress() == baseBind->getAddress());
            }
          }
        }
      }
    }
  }
}
