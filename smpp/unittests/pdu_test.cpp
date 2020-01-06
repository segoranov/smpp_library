#include "pdu/pdu.h"

#include <cereal/archives/binary.hpp>
#include <sstream>

#include "catch.hpp"
#include "pdu/bind_transmitter.h"
#include "pdu/bind_transmitter_resp.h"
#include "pdu/builder/bind_transmitter_builder.h"
#include "pdu/builder/bind_transmitter_resp_builder.h"
#include "pdu/builder/submit_sm_builder.h"
#include "smpp_constants.h"
#include "smpp_exceptions.h"
#include "util/smpp_util.h"

SCENARIO("Pdu is serialized/deserialized properly", "[pdu]") {
  GIVEN("A sample BindTransmitter pdu defined as raw data (array of hex bytes)") {
    /*
    Sample PDU (Values are shown in Hex format):
    00 00 00 2F 00 00 00 02 00 00 00 00 00 00 00 01
    53 4D 50 50 33 54 45 53 54 00 73 65 63 72 65 74
    30 38 00 53 55 42 4D 49 54 31 00 50 01 01 00

    The 16-octet header would be decoded as follows:
    00 00 00 2F Command Length 0x0000002F (47 in decimal)
    00 00 00 02 Command ID 0x00000002 (id of bind transmitter)
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

    const uint8_t samplePdu[] = {0x00, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x53, 0x4D, 0x50, 0x50,
                                 0x33, 0x54, 0x45, 0x53, 0x54, 0x00, 0x73, 0x65, 0x63, 0x72,
                                 0x65, 0x74, 0x30, 0x38, 0x00, 0x53, 0x55, 0x42, 0x4D, 0x49,
                                 0x54, 0x31, 0x00, 0x50, 0x01, 0x01, 0x00};

    THEN("The size of the sample pdu should be 47") { REQUIRE(sizeof(samplePdu) == 47); }

    AND_GIVEN("a BindTransmitter PDU corresponding to the raw PDU") {
      smpp::BindTransmitter bindTransmitterPdu{
          smpp::builder::BindTransmitterBuilder()
              .withCommandLength(47)  // 0x0000002F in hex is 47 in decimal
              .withCommandStatus(0)
              .withSequenceNumber(1)
              .withSystemId("SMPP3TEST")
              .withPassword("secret08")
              .withSystemType("SUBMIT1")
              .withInterfaceVersion(0x50)
              .withAddrTon(0x01)
              .withAddrNpi(0x01)
              .withAddressRange("")};

      WHEN("the BindTransmitter PDU is serialized into a stringstream") {
        std::stringstream ss;
        bindTransmitterPdu.serialize(ss);

        THEN("the stringstream size should be 47 bytes (the command length)") {
          REQUIRE(ss.str().size() == 47);
        }

        THEN(
            "the string from the stringstream should be equal to the string created by the raw "
            "PDU") {
          REQUIRE(ss.str() == std::string{(char*)samplePdu, sizeof(samplePdu)});
        }

        AND_WHEN("a BindTransmitter PDU is deserialized from the stringstream") {
          auto deserializedPdu = smpp::Pdu::deserialize(ss);
          REQUIRE(deserializedPdu->getCommandId() == smpp::constants::CMD_ID_BIND_TRANSMITTER);

          auto deserializedBindTransmitterPdu =
              dynamic_cast<smpp::BindTransmitter*>(deserializedPdu.get());
          REQUIRE(deserializedBindTransmitterPdu);

          THEN("the deserialized PDU should correspond to the initial PDU") {
            REQUIRE(deserializedBindTransmitterPdu->getCommandLength() ==
                    bindTransmitterPdu.getCommandLength());

            REQUIRE(deserializedBindTransmitterPdu->getCommandStatus() ==
                    bindTransmitterPdu.getCommandStatus());

            REQUIRE(deserializedBindTransmitterPdu->getSequenceNumber() ==
                    bindTransmitterPdu.getSequenceNumber());

            REQUIRE(deserializedBindTransmitterPdu->getSystemId() ==
                    bindTransmitterPdu.getSystemId());

            REQUIRE(deserializedBindTransmitterPdu->getPassword() ==
                    bindTransmitterPdu.getPassword());

            REQUIRE(deserializedBindTransmitterPdu->getSystemType() ==
                    bindTransmitterPdu.getSystemType());

            REQUIRE(deserializedBindTransmitterPdu->getInterfaceVersion() ==
                    bindTransmitterPdu.getInterfaceVersion());

            REQUIRE(deserializedBindTransmitterPdu->getAddrTon() ==
                    bindTransmitterPdu.getAddrTon());

            REQUIRE(deserializedBindTransmitterPdu->getAddrNpi() ==
                    bindTransmitterPdu.getAddrNpi());

            REQUIRE(deserializedBindTransmitterPdu->getAddressRange() ==
                    bindTransmitterPdu.getAddressRange());
          }
        }
      }
    }
  }

  GIVEN("A sample BindTransmitterResp pdu defined as raw data (array of hex bytes)") {
    /*
    Sample PDU (Values are shown in Hex format):
    00 00 00 2F 80 00 00 02 00 00 00 00 00 00 00 01
    53 4D 50 50 33 54 45 53 54 00 02 10 00 01 01

    The 16-octet header would be decoded as follows:
    00 00 00 1F Command Length 0x0000002F (31 in decimal)
    80 00 00 02 Command ID 0x80000002 (id of bind transmitter resp)
    00 00 00 00 Command Status 0x00000000
    00 00 00 01 Sequence Number 0x00000001

    The remaining data represents the PDU body (which in this example relates to the
    bind_transmitter_resp PDU).
    This is diagnosed as follows:
    53 4D 50 50 33 54 45 53 54 00       system_id (“SMPP3TEST”)
    02 10                               TLV sc_interface_version tag
    00 01                               TLV sc_interface_version length
    01                                  TLV sc_interface_version value
    */

    const uint8_t samplePdu[] = {0x00, 0x00, 0x00, 0x1F, 0x80, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
                                 0x00, 0x00, 0x00, 0x00, 0x01, 0x53, 0x4D, 0x50, 0x50, 0x33, 0x54,
                                 0x45, 0x53, 0x54, 0x00, 0x02, 0x10, 0x00, 0x01, 0x01};

    THEN("The size of the sample pdu should be 31") { REQUIRE(sizeof(samplePdu) == 31); }

    AND_GIVEN("a BindTransmitterResp PDU corresponding to the raw PDU") {
      smpp::BindTransmitterResp bindTransmitterRespPdu{
          smpp::builder::BindTransmitterRespBuilder()
              .withCommandLength(31)
              .withCommandStatus(0)
              .withSequenceNumber(1)
              .withSystemId("SMPP3TEST")
              .withOptionalParameter(smpp::Tlv{smpp::constants::TAG_SC_INTERFACE_VERSION,
                                               static_cast<uint8_t>(0x01)})};

      WHEN("the BindTransmitterResp PDU is serialized into a stringstream") {
        std::stringstream ss;
        bindTransmitterRespPdu.serialize(ss);

        THEN("the stringstream size should be 31 bytes (the command length)") {
          REQUIRE(ss.str().size() == 31);
        }

        THEN(
            "the string from the stringstream should be equal to the string created by the raw "
            "PDU") {
          REQUIRE(ss.str() == std::string{(char*)samplePdu, sizeof(samplePdu)});
        }

        AND_WHEN("a BindTransmitterResp PDU is deserialized from the stringstream") {
          auto deserializedPdu = smpp::Pdu::deserialize(ss);
          REQUIRE(deserializedPdu->getCommandId() ==
                  smpp::constants::CMD_ID_BIND_TRANSMITTER_RESP);

          REQUIRE(
              deserializedPdu->hasOptionalParameter(smpp::constants::TAG_SC_INTERFACE_VERSION));

          auto deserializedSubmitSmPdu =
              dynamic_cast<smpp::BindTransmitterResp*>(deserializedPdu.get());
          REQUIRE(deserializedSubmitSmPdu);

          THEN("the deserialized PDU should correspond to the initial PDU") {
            REQUIRE(deserializedSubmitSmPdu->getCommandLength() ==
                    bindTransmitterRespPdu.getCommandLength());

            REQUIRE(deserializedSubmitSmPdu->getCommandStatus() ==
                    bindTransmitterRespPdu.getCommandStatus());

            REQUIRE(deserializedSubmitSmPdu->getSequenceNumber() ==
                    bindTransmitterRespPdu.getSequenceNumber());

            REQUIRE(deserializedSubmitSmPdu->getSystemId() ==
                    bindTransmitterRespPdu.getSystemId());

            REQUIRE(deserializedSubmitSmPdu->getOptionalParameters().size() == 1);
            REQUIRE(
                deserializedSubmitSmPdu->getOptionalParameters()[0] ==
                smpp::Tlv{smpp::constants::TAG_SC_INTERFACE_VERSION, static_cast<uint8_t>(0x01)});
          }
        }
      }
    }
  }

  GIVEN("A sample submit sm pdu") {
    smpp::SubmitSm submitSmPdu{smpp::builder::SubmitSmBuilder()
                                   .withCommandLength(44)
                                   .withCommandStatus(0)
                                   .withSequenceNumber(378019)
                                   .withServiceType("A")
                                   .withSourceAddrTon(0x03)
                                   .withSourceAddrNpi(0x01)
                                   .withSourceAddr("B")
                                   .withDestAddrTon(0x03)
                                   .withDestAddrNpi(0x01)
                                   .withDestinationAddr("C")
                                   .withEsmClass(0)
                                   .withProtocolId(0)
                                   .withPriorityFlag(0)
                                   .withScheduleDeliveryTime("")
                                   .withValidityPeriod("D")
                                   .withRegisteredDelivery(0x01)
                                   .withReplaceIfPresentFlag(0)
                                   .withDataCoding(0)
                                   .withSmDefaultMsgId(0)
                                   .withSmLength(7)
                                   .withShortMessage("TEST_SM")};

    WHEN("the submit sm PDU is serialized into a stringstream") {
      std::stringstream ss;
      submitSmPdu.serialize(ss);

      THEN("the stringstream size should be 44 bytes (the command length)") {
        REQUIRE(ss.str().size() == 44);
      }

      AND_WHEN("a submit sm PDU is deserialized from the stringstream") {
        auto deserializedPdu = smpp::Pdu::deserialize(ss);

        REQUIRE(deserializedPdu->getCommandId() == smpp::constants::CMD_ID_SUBMIT_SM);

        auto deserializedSubmitSmPdu = dynamic_cast<smpp::SubmitSm*>(deserializedPdu.get());
        REQUIRE(deserializedSubmitSmPdu);

        THEN("the deserialized PDU should correspond to the initial PDU") {
          REQUIRE(deserializedSubmitSmPdu->getCommandLength() == submitSmPdu.getCommandLength());
          REQUIRE(deserializedSubmitSmPdu->getCommandStatus() == submitSmPdu.getCommandStatus());
          REQUIRE(deserializedSubmitSmPdu->getSequenceNumber() == submitSmPdu.getSequenceNumber());
          REQUIRE(deserializedSubmitSmPdu->getShortMessage() == submitSmPdu.getShortMessage());
          REQUIRE(deserializedSubmitSmPdu->getOptionalParameters().size() == 0);
        }
      }
    }
  }
}

SCENARIO("Deserialiation of malformed PDUs throws proper exceptions", "[malformed_pdu]") {
  GIVEN("A stream containing invalid command id - 12 (0x00 0x00 0x00 0x0C in hex)") {
    const char rawDataPduWithInvalidCommandLength[] = {
        0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x01, 0x53, 0x4D, 0x50, 0x50, 0x33, 0x54, 0x45, 0x53,
        0x54, 0x00, 0x73, 0x65, 0x63, 0x72, 0x65, 0x74, 0x30, 0x38, 0x00, 0x53,
        0x55, 0x42, 0x4D, 0x49, 0x54, 0x31, 0x00, 0x50, 0x01, 0x01, 0x00};

    std::stringstream ss{std::string{rawDataPduWithInvalidCommandLength,
                                     sizeof(rawDataPduWithInvalidCommandLength)}};

    WHEN("We try to deserialize a PDU") {
      THEN("InvalidCommandLengthException should be thrown") {
        REQUIRE_THROWS_AS(smpp::Pdu::deserialize(ss), smpp::InvalidCommandLengthException);
      }
    }
  }

  GIVEN("A stream containing invalid command id - 0x77 0x00 0x00 0x77") {
    const char rawDataPduWithInvalidCommandId[] = {
        0x00, 0x00, 0x00, 0x2F, 0x77, 0x00, 0x00, 0x77, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x01, 0x53, 0x4D, 0x50, 0x50, 0x33, 0x54, 0x45, 0x53,
        0x54, 0x00, 0x73, 0x65, 0x63, 0x72, 0x65, 0x74, 0x30, 0x38, 0x00, 0x53,
        0x55, 0x42, 0x4D, 0x49, 0x54, 0x31, 0x00, 0x50, 0x01, 0x01, 0x00};

    std::stringstream ss{
        std::string{rawDataPduWithInvalidCommandId, sizeof(rawDataPduWithInvalidCommandId)}};

    WHEN("We try to deserialize a PDU") {
      THEN("InvalidCommandIdException should be thrown") {
        REQUIRE_THROWS_AS(smpp::Pdu::deserialize(ss), smpp::InvalidCommandIdException);
      }
    }
  }
}
