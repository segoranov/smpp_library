#include "type/address.h"

#include <cereal/archives/binary.hpp>

#include "catch.hpp"

SCENARIO("Address should be serialized and deserialized properly", "[address]") {
  GIVEN("an address") {
    smpp::Address address(1, 2, "test_address_space");
    AND_GIVEN("A stringstream") {
      std::stringstream ss;

      WHEN("the address is serialized to the stringstream by BinaryOutputArchive") {
        {
          cereal::BinaryOutputArchive oarchive{ss};
          oarchive(address);  // Write the address to the archive
        }  // archive goes out of scope, ensuring all contents are flushed to the underlying
           // stream

        THEN("the stringstream size should be equal to the address size") {
          REQUIRE(ss.str().size() == address.size());
        }

        AND_WHEN("an address is deserialized from the stringstream") {
          smpp::Address deserializedAddress;
          REQUIRE(deserializedAddress != address);

          {
            cereal::BinaryInputArchive iarchive{ss};
            iarchive(deserializedAddress);  // Read the data from the archive into the address
          }

          THEN("the deserialized address should correspond to the initial address") {
            REQUIRE(deserializedAddress == address);
          }
        }
      }
    }
  }
}