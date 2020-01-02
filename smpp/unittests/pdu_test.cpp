#include "pdu/pdu.h"

#include <cereal/archives/binary.hpp>
#include <sstream>

#include "catch.hpp"
#include "pdu/bind_transmitter.h"
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

    AND_GIVEN("a BindTransmitter PDU corresponding to the raw PDU") {
      std::shared_ptr<smpp::BindTransmitter> bindTransmitterPdu =
          smpp::BindTransmitter::createEmpty();

      bindTransmitterPdu->setCommandLength(47);  // 0x0000002F in hex is 47 in decimal
      bindTransmitterPdu->setCommandStatus(0);   // 0x00000000
      bindTransmitterPdu->setSequenceNumber(1);  // 0x00000001
      bindTransmitterPdu->setSystemId("SMPP3TEST");
      bindTransmitterPdu->setPassword("secret08");
      bindTransmitterPdu->setSystemType("SUBMIT1");
      bindTransmitterPdu->setInterfaceVersion(0x50);
      smpp::Address address{0x01, 0x01};
      bindTransmitterPdu->setAddress(address);

      WHEN("the BindTransmitter PDU is serialized into a stringstream") {
        std::stringstream ss;
        bindTransmitterPdu->serialize(ss);

        THEN("the stringstream size should be 47 bytes (the command length)") {
          REQUIRE(ss.str().size() == 47);
        }

        THEN(
            "the string from the stringstream should be equal to the string created by the raw "
            "PDU") {
          REQUIRE(ss.str() == std::string{samplePdu, sizeof(samplePdu)});
        }

        AND_WHEN("a BindTransmitter PDU is deserialized from the stringstream") {
          auto deserializedPdu = smpp::Pdu::deserialize(ss);
          REQUIRE(deserializedPdu->getCommandId() == smpp::constants::CMD_ID_BIND_TRANSMITTER);

          auto deserializedBindTransmitterPdu =
              dynamic_cast<smpp::BindTransmitter*>(deserializedPdu.get());
          REQUIRE(deserializedBindTransmitterPdu);

          THEN("the deserialized PDU should correspond to the initial PDU") {
            REQUIRE(deserializedBindTransmitterPdu->getCommandLength() ==
                    bindTransmitterPdu->getCommandLength());

            REQUIRE(deserializedBindTransmitterPdu->getCommandStatus() ==
                    bindTransmitterPdu->getCommandStatus());

            REQUIRE(deserializedBindTransmitterPdu->getSequenceNumber() ==
                    bindTransmitterPdu->getSequenceNumber());

            REQUIRE(deserializedBindTransmitterPdu->getSystemId() ==
                    bindTransmitterPdu->getSystemId());

            REQUIRE(deserializedBindTransmitterPdu->getPassword() ==
                    bindTransmitterPdu->getPassword());

            REQUIRE(deserializedBindTransmitterPdu->getSystemType() ==
                    bindTransmitterPdu->getSystemType());

            REQUIRE(deserializedBindTransmitterPdu->getInterfaceVersion() ==
                    bindTransmitterPdu->getInterfaceVersion());

            REQUIRE(deserializedBindTransmitterPdu->getAddress() ==
                    bindTransmitterPdu->getAddress());
          }
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
