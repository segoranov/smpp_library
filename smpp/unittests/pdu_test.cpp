#include "pdu/pdu.h"

#include <cereal/archives/binary.hpp>
#include <sstream>

#include "catch.hpp"
#include "pdu/bindtransmitter.h"
#include "smppconstants.h"
#include "smppexceptions.h"
#include "util/smpp_util.h"

SCENARIO("Pdu header is serialized/deserialized properly", "[pdu_header]") {
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

    AND_GIVEN("a sample BindTransmitter PDU corresponding to the raw PDU") {
      smpp::BindTransmitter bindTransmitterPdu;
      bindTransmitterPdu.setCommandLength(47);  // 0x0000002F in hex is 47 in decimal
      bindTransmitterPdu.setCommandStatus(0);   // 0x00000000
      bindTransmitterPdu.setSequenceNumber(1);  // 0x00000001
      bindTransmitterPdu.setSystemId("SMPP3TEST");
      bindTransmitterPdu.setPassword("secret08");
      bindTransmitterPdu.setSystemType("SUBMIT1");
      bindTransmitterPdu.setInterfaceVersion(0x50);
      smpp::Address address{0x01, 0x01};
      bindTransmitterPdu.setAddress(address);

      WHEN("the BindTransmitter PDU is serialized into a stringstream") {
        auto ss =
            smpp::util::serializePdu<smpp::BindTransmitter, std::stringstream>(bindTransmitterPdu);

        THEN("the stringstream size should be 47 bytes (the command length)") {
          REQUIRE(ss.str().size() == 47);
        }

        THEN(
            "the string from the stringstream should be equal to the string created by the raw "
            "PDU") {
          REQUIRE(ss.str() == std::string{samplePdu, sizeof(samplePdu)});
        }

        AND_WHEN(
            "a BindTransmitter PDU is deserialized from the stringstream by "
            "BinaryInputArchive") {
          smpp::BindTransmitter deserializedBindTransmitter;
          {
            cereal::BinaryInputArchive iarchive{ss};
            iarchive(deserializedBindTransmitter);  // Read the data from the archive into the PDU
          }

          THEN("the deserialized PDU should correspond to the initial PDU") {
            REQUIRE(deserializedBindTransmitter.getCommandLength() ==
                    bindTransmitterPdu.getCommandLength());

            REQUIRE(deserializedBindTransmitter.getCommandStatus() ==
                    bindTransmitterPdu.getCommandStatus());

            REQUIRE(deserializedBindTransmitter.getSequenceNumber() ==
                    bindTransmitterPdu.getSequenceNumber());

            REQUIRE(deserializedBindTransmitter.getSystemId() == bindTransmitterPdu.getSystemId());

            REQUIRE(deserializedBindTransmitter.getPassword() == bindTransmitterPdu.getPassword());

            REQUIRE(deserializedBindTransmitter.getSystemType() ==
                    bindTransmitterPdu.getSystemType());

            REQUIRE(deserializedBindTransmitter.getInterfaceVersion() ==
                    bindTransmitterPdu.getInterfaceVersion());

            REQUIRE(deserializedBindTransmitter.getAddress() == bindTransmitterPdu.getAddress());
          }
        }
      }
    }
  }
}
