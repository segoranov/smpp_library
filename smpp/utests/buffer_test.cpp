

#include "aliases.h"
#include "pdu/pdu.h"
#include "catch.hpp"
#include "transcoder/pdu_transcoder.h"

SCENARIO("Buffer should know it's size and clear itself properly", "[buffer]") {
  GIVEN("An empty channel buffer") {
    smpp::Buffer channelBuffer;
    REQUIRE(channelBuffer.isEmpty());
    REQUIRE(channelBuffer.size() == 0);
    WHEN("a character is written to the buffer") {
      channelBuffer.writeChar('c');
      THEN("the buffer should not be empty") { REQUIRE(!channelBuffer.isEmpty()); }
      THEN("the size of the buffer should be 1") { REQUIRE(channelBuffer.size() == 1); }

      WHEN("the buffer is cleared") {
        channelBuffer.clear();
        THEN("the buffer should be empty") { REQUIRE(channelBuffer.isEmpty()); }
        THEN("the size of the buffer should be 0") { REQUIRE(channelBuffer.size() == 0); }
      }
    }
  }
}

SCENARIO("Buffer reads and writes single values properly", "[buffer]") {
  GIVEN("A channel buffer and some values with different sizes") {
    smpp::Buffer channelBuffer;
    constexpr char ch{'a'};
    constexpr uint8_t x8{26};
    constexpr uint16_t x16{1000};
    constexpr uint32_t x32{999'999'999};
    const std::string octetString{"just_a_test_octet_string"};
    constexpr char nullTerminatedString[] = "constString";

    WHEN("the char is written to the buffer") {
      channelBuffer.writeInt8(ch);
      THEN("the size of the buffer should be 1 byte") { REQUIRE(channelBuffer.size() == 1); }
      THEN("the char value read from the buffer should be the same") {
        REQUIRE(channelBuffer.readChar() == ch);
      }
    }

    WHEN("the uint8_value is written to the buffer") {
      channelBuffer.writeInt8(x8);
      THEN("the size of the buffer should be 1 byte") { REQUIRE(channelBuffer.size() == 1); }
      THEN("the uint8_t value read from the buffer should be the same") {
        REQUIRE(channelBuffer.readInt8() == x8);
      }
    }

    WHEN("the uint16_value is written to the buffer") {
      channelBuffer.writeInt16(x16);
      THEN("the size of the buffer should be 2 bytes") { REQUIRE(channelBuffer.size() == 2); }
      THEN("the uint16_t value read from the buffer should be the same") {
        REQUIRE(channelBuffer.readInt16() == x16);
      }
    }

    WHEN("the uint32_value is written to the buffer") {
      channelBuffer.writeInt32(x32);
      THEN("the size of the buffer should be 4 bytes") { REQUIRE(channelBuffer.size() == 4); }
      THEN("the uint32_t value read from the buffer should be the same") {
        REQUIRE(channelBuffer.readInt32() == x32);
      }
    }

    WHEN("the octet string is written to the buffer") {
      channelBuffer.writeOctetString(octetString);
      THEN("the size of the buffer should corrsepond to the string size") {
        REQUIRE(channelBuffer.size() == octetString.size());
      }
      THEN("the uint32_t value read from the buffer should be the same") {
        REQUIRE(channelBuffer.readString(octetString.size()) == octetString);
      }
    }

    WHEN("the null terminated string is written to the buffer") {
      channelBuffer.writeNullTerminatedString(nullTerminatedString);
      THEN(
          "the size of the buffer should corrsepond to the string size + 1 because of the null "
          "terminator"
          "terminator") {
        REQUIRE(channelBuffer.size() == std::string{nullTerminatedString}.size() + 1);
      }
      THEN("the string value read from the buffer should be the same") {
        REQUIRE(std::string{channelBuffer.readNullTerminatedString()} == nullTerminatedString);
      }
    }
  }
}

SCENARIO("Buffer reads and writes multiple values properly", "[buffer]") {
  GIVEN("A channel buffer and some values with different sizes") {
    smpp::Buffer channelBuffer;
    constexpr char ch{'a'};
    constexpr uint8_t x8{26};
    constexpr uint16_t x16{1000};
    constexpr uint32_t x32{999'999'999};
    const std::string octetString{"just_a_test_octet_string"};
    constexpr char nullTerminatedString[] = "constString";

    WHEN("all the values are written to the buffer") {
      channelBuffer.writeChar(ch);
      channelBuffer.writeInt8(x8);
      channelBuffer.writeInt16(x16);
      channelBuffer.writeInt32(x32);
      channelBuffer.writeOctetString(octetString);
      channelBuffer.writeNullTerminatedString(nullTerminatedString);
      THEN(
          "if we read them in the same order that we wrote them to the buffer, the values should "
          "be the same") {
        REQUIRE(channelBuffer.readChar() == ch);
        REQUIRE(channelBuffer.readInt8() == x8);
        REQUIRE(channelBuffer.readInt16() == x16);
        REQUIRE(channelBuffer.readInt32() == x32);
        REQUIRE(channelBuffer.readString(octetString.size()) == octetString);
        REQUIRE(channelBuffer.readNullTerminatedString() == nullTerminatedString);
      }
    }
  }
}