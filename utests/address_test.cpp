#include "../smpp/type/address.h"

#include "catch.hpp"

SCENARIO("Address should be read and written properly to buffer", "[address]") {
  GIVEN("An empty channel buffer and an address") {
    smpp::ChannelBuffer channelBuffer;
    smpp::Address address(1, 2, "test_address_space");
    WHEN("the address is written to the buffer") {
      address.write(channelBuffer);

      THEN("the buffer size should be equal to the address size") {
        channelBuffer.size() == address.size();
      }

      THEN("after constructing a new address from the buffer, it should be equal to the first address") {
          smpp::Address reconstructedAddress{channelBuffer.readInt8(), channelBuffer.readInt8(), channelBuffer.readNullTerminatedString()};
          REQUIRE(reconstructedAddress.size() == address.size());
          REQUIRE(reconstructedAddress == address);
      }
    }
  }
}