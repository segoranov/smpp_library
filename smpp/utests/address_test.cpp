#include "catch.hpp"
#include "util/buffer_util.h"

SCENARIO("Address should be read and written properly to buffer", "[address]") {
  GIVEN("An empty buffer") {
    smpp::Buffer buffer;

    AND_GIVEN("an adress") {
      smpp::Address address(1, 2, "test_address_space");
      WHEN("the address is written to the buffer") {
        smpp::buffer_util::writeAddress(buffer, address);

        THEN("the buffer size should be equal to the address size") {
          buffer.size() == address.size();
        }

        THEN(
            "after constructing a new address from the buffer, it should be equal to the first "
            "address") {
          auto reconstructedAddress = smpp::buffer_util::readAddress(buffer);
          REQUIRE(reconstructedAddress.size() == address.size());
          REQUIRE(reconstructedAddress == address);
        }
      }
    }
  }
}