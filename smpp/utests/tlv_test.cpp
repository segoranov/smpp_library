#include "catch.hpp"
#include "smppconstants.h"
#include "util/buffer_util.h"

SCENARIO("Tlv should have correct size", "[tlv]") {
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

SCENARIO("Tlv should be written/read properly from buffer", "[tlv]") {
  GIVEN("An empty buffer and a TLV") {
    smpp::Buffer buffer;

    std::string test_value{"billing_identification_test_value"};
    smpp::Tlv tlv{smpp::constants::TAG_BILLING_IDENTIFICATION, test_value};

    WHEN("the TLV is written to the buffer") {
      smpp::buffer_util::writeTlv(buffer, tlv);
      THEN("the buffer size should be equal to the TLV size") {
        CAPTURE(buffer.size(), tlv.size());
        REQUIRE(buffer.size() == tlv.size());
      }
      THEN("after reading TLV from buffer, the read TLV should be the equal to the initial TLV") {
        auto readTlv = smpp::buffer_util::readTlv(buffer);
        REQUIRE(readTlv == tlv);
      }
    }
  }
}
