#include "catch.hpp"
#include "util/buffer_util.h"

SCENARIO("Address should be read and written properly to buffer", "[address]") {
  GIVEN("An empty channel buffer and an address") {
    smpp::Buffer channelBuffer;
    smpp::Address address(1, 2, "test_address_space");
    WHEN("the address is written to the buffer") {
      smpp::buffer_util::writeAddress(channelBuffer, address);

      THEN("the buffer size should be equal to the address size") {
        channelBuffer.size() == address.size();
      }

      THEN(
          "after constructing a new address from the buffer, it should be equal to the first "
          "address") {
        auto reconstructedAddress = smpp::buffer_util::readAddress(channelBuffer);
        REQUIRE(reconstructedAddress.size() == address.size());
        REQUIRE(reconstructedAddress == address);
      }
    }
  }
}