

#include "../smpp/aliases.h"
#include "../smpp/pdu/pdu.h"
#include "../smpp/transcoder/pdu_transcoder.h"
#include "catch.hpp"

SCENARIO("ChannelBuffer reads and writes values properly", "[buffer]") {
  GIVEN("A channel buffer and some values with different sizes") {
    smpp::ChannelBuffer channelBuffer;
    constexpr uint8_t x8{26};
    constexpr uint16_t x16{1000};
    constexpr uint32_t x32{999999999};

    WHEN("the uint8_value is written to the buffer") {
      channelBuffer.writeInt8(x8);
      THEN("the uint8_t value read from the buffer should be the same") {
        channelBuffer.resetMarker();
        REQUIRE(x8 == channelBuffer.readInt8());
      }
    }

    WHEN("the uint16_value is written to the buffer") {
      channelBuffer.writeInt16(x16);
      THEN("the uint16_t value read from the buffer should be the same") {
        channelBuffer.resetMarker();
        REQUIRE(x16 == channelBuffer.readInt16());
      }
    }

    WHEN("the uint32_value is written to the buffer") {
      channelBuffer.writeInt32(x32);
      THEN("the uint32_t value read from the buffer should be the same") {
        channelBuffer.resetMarker();
        REQUIRE(x32 == channelBuffer.readInt32());
      }
    }
  }
}