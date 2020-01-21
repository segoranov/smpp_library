#include <sstream>

#include "catch.hpp"
#include "smpp/pdu/submit_multi.h"
#include "smpp/smpp_constants.h"

SCENARIO("Destination addresses should have correct size", "[dest_addr]") {
  GIVEN("3 SME dest addresses and 3 distribution list addresses") {
    // Check the smpp specification to clarify the sizes and structures for yourself

    smpp::SubmitMultiDestinationAddresses destAddresses;
    destAddresses.addSMEDestAddress(
        smpp::SMEDestAddress{0x01, 0x01, "TEST1"});  // 1 + 1 + 1 + 5 + 1  = 9 bytes
    destAddresses.addSMEDestAddress(
        smpp::SMEDestAddress{0x01, 0x01, "TEST23"});  // 1 + 1 + 1 + 6 + 1  = 10 bytes
    destAddresses.addSMEDestAddress(
        smpp::SMEDestAddress{0x01, 0x01, "TEST345"});  // 1 + 1 + 1 + 7 + 1  = 11 bytes

    destAddresses.addDistributionListDestAddress(
        smpp::DistributionListDestAddress{"TEST_DLNAME_1"});  // 1 + 13 + 1 = 15 bytes
    destAddresses.addDistributionListDestAddress(
        smpp::DistributionListDestAddress{"TEST_DLNAME_23"});  // 1 + 14 + 1 = 16 bytes
    destAddresses.addDistributionListDestAddress(
        smpp::DistributionListDestAddress{"TEST_DLNAME_345"});  // 1 + 15 + 1 = 17 bytes

    /* Total size should be 79:
        number of dests -> 1 byte
        3 SME dest addresses -> 9 + 10 + 11 = 30 bytes;
        3 Distribution list dest addresses -> 15 + 16 + 17 = 48 bytes

        Total: 1 + 30 + 48 = 79
    */

    THEN("the number of dests should be 6") { REQUIRE(destAddresses.getNumberOfDests() == 6); }
    THEN("the size of the destination addresses structure should be 79") {
      REQUIRE(destAddresses.size() == 79);
    }

    WHEN("we serialize the addresses in a stringstream") {
      std::stringstream ss;
      destAddresses.serialize(ss);
      THEN("the size of the string in the stringstream should be 79") {
        REQUIRE(ss.str().size() == 79);
      }

      AND_WHEN("we deserialize a new structure from the stream") {
        smpp::SubmitMultiDestinationAddresses deserialized;
        deserialized.deserialize(ss);

        THEN("the deserialized structure should be 79 bytes of size") {
          REQUIRE(deserialized.size() == 79);
        }

        AND_THEN("the old and new structures should be equal") {
          REQUIRE(deserialized == destAddresses);
        }
      }
    }
  }
}
