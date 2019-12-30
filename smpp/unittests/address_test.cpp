#include "type/address.h"

#include <cereal/archives/binary.hpp>

#include "catch.hpp"

SCENARIO("Address should be serialized and deserialized properly", "[address]") {
  GIVEN("an address") {
    smpp::Address address(1, 2, "test_address_space");
    AND_GIVEN("A stringstream") {
      std::stringstream ss;

      WHEN("the address is serialized to the stringstream") {
        address.serialize(ss);

        THEN("the stringstream size should be equal to the address size") {
          REQUIRE(ss.str().size() == address.size());
        }

        AND_WHEN("an address is deserialized from the stringstream") {
          smpp::Address deserializedAddress;
          REQUIRE(deserializedAddress != address);
          deserializedAddress.deserialize(ss);

          THEN("the deserialized address should correspond to the initial address") {
            REQUIRE(deserializedAddress == address);
          }
        }
      }
    }
  }
}