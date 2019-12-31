#include "tlv/tlv.h"

#include "catch.hpp"
#include "cereal/archives/binary.hpp"
#include "smpp_constants.h"

SCENARIO("Tlv should have correct size", "[Tlv]") {
  GIVEN("some test values with different types and sizes") {
    std::string strTestValue{"billing_identification_test_value"};
    uint8_t x8{0};
    uint16_t x16{1};
    uint32_t x32{1};

    WHEN("a string test value is used to construct TLV") {
      smpp::Tlv tlv{smpp::constants::TAG_BILLING_IDENTIFICATION, strTestValue};
      THEN("the tlv size should be equal to '4 + the string size'")
      REQUIRE(tlv.size() == 4 + strTestValue.size());
    }

    WHEN("a uint8_t test value is used to construct TLV") {
      smpp::Tlv tlv{smpp::constants::TAG_ALERT_ON_MESSAGE_DELIVERY, x8};
      THEN("the tlv size should be equal to 5 bytes")
      REQUIRE(tlv.size() == 5);
    }

    WHEN("a uint16_t test value is used to construct TLV") {
      smpp::Tlv tlv{smpp::constants::TAG_ALERT_ON_MESSAGE_DELIVERY, x16};
      THEN("the tlv size should be equal to 6 bytes")
      REQUIRE(tlv.size() == 6);
    }

    WHEN("a uint32_t test value is used to construct TLV") {
      smpp::Tlv tlv{smpp::constants::TAG_ALERT_ON_MESSAGE_DELIVERY, x32};
      THEN("the tlv size should be equal to 8 bytes")
      REQUIRE(tlv.size() == 8);
    }
  }
}

SCENARIO("Tlv should be serialized and deserialized properly", "[Tlv]") {
  GIVEN("a sample Tlv") {
    std::string strTestValue{"billing_identification_test_value"};
    smpp::Tlv tlv{smpp::constants::TAG_BILLING_IDENTIFICATION, strTestValue};

    AND_GIVEN("A stringstream") {
      std::stringstream ss;

      WHEN("the Tlv is serialized to the stringstream by BinaryOutputArchive") {
        {
          cereal::BinaryOutputArchive oarchive{ss};
          oarchive(tlv);  // Write the Tlv to the archive
        }  // archive goes out of scope, ensuring all contents are flushed to the underlying
           // stream

        THEN("the stringstream size should be equal to the Tlv size") {
          REQUIRE(ss.str().size() == tlv.size());
        }

        AND_WHEN("a Tlv is deserialized from the stringstream") {
          smpp::Tlv deserializedTlv;
          REQUIRE(deserializedTlv != tlv);

          {
            cereal::BinaryInputArchive iarchive{ss};
            iarchive(deserializedTlv);  // Read the data from the archive into the Tlv
          }

          THEN("the deserialized Tlv should correspond to the initial Tlv") {
            REQUIRE(deserializedTlv == tlv);
          }
        }
      }
    }
  }
}