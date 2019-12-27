

#include <iostream>
#include <memory>

#include "aliases.h"
#include "catch.hpp"
#include "pdu/bindtransmitter.h"
#include "pdu/pdu.h"
#include "smppconstants.h"
#include "tlv/tlv.h"
#include "transcoder/pdu_transcoder.h"
#include "util/buffer_util.h"
#include "util/print_util.h"

SCENARIO("Buffer should know it's size and clear itself properly", "[buffer]") {
  GIVEN("An empty buffer") {
    smpp::Buffer buffer;
    REQUIRE(buffer.isEmpty());
    REQUIRE(buffer.size() == 0);
    WHEN("a character is written to the buffer") {
      buffer.writeChar('c');
      THEN("the buffer should not be empty") { REQUIRE(!buffer.isEmpty()); }
      THEN("the size of the buffer should be 1") { REQUIRE(buffer.size() == 1); }

      WHEN("the buffer is cleared") {
        buffer.clear();
        THEN("the buffer should be empty") { REQUIRE(buffer.isEmpty()); }
        THEN("the size of the buffer should be 0") { REQUIRE(buffer.size() == 0); }
      }
    }
  }
}

SCENARIO("Buffer reads and writes single values properly", "[buffer]") {
  GIVEN("A buffer and some values with different sizes") {
    smpp::Buffer buffer;
    constexpr char ch{'a'};
    constexpr uint8_t x8{26};
    constexpr uint16_t x16{1000};
    constexpr uint32_t x32{999'999'999};
    const std::string octetString{"just_a_test_octet_string"};
    constexpr char nullTerminatedString[] = "constString";

    WHEN("the char is written to the buffer") {
      buffer.writeInt8(ch);
      THEN("the size of the buffer should be 1 byte") { REQUIRE(buffer.size() == 1); }
      THEN("the char value read from the buffer should be the same") {
        REQUIRE(buffer.readChar() == ch);
      }
    }

    WHEN("the uint8_value is written to the buffer") {
      buffer.writeInt8(x8);
      THEN("the size of the buffer should be 1 byte") { REQUIRE(buffer.size() == 1); }
      THEN("the uint8_t value read from the buffer should be the same") {
        REQUIRE(buffer.readInt8() == x8);
      }
    }

    WHEN("the uint16_value is written to the buffer") {
      buffer.writeInt16(x16);
      THEN("the size of the buffer should be 2 bytes") { REQUIRE(buffer.size() == 2); }
      THEN("the uint16_t value read from the buffer should be the same") {
        REQUIRE(buffer.readInt16() == x16);
      }
    }

    WHEN("the uint32_value is written to the buffer") {
      buffer.writeInt32(x32);
      THEN("the size of the buffer should be 4 bytes") { REQUIRE(buffer.size() == 4); }
      THEN("the uint32_t value read from the buffer should be the same") {
        REQUIRE(buffer.readInt32() == x32);
      }
    }

    WHEN("the octet string is written to the buffer") {
      buffer.writeOctetString(octetString);
      THEN("the size of the buffer should corrsepond to the string size") {
        REQUIRE(buffer.size() == octetString.size());
      }
      THEN("the uint32_t value read from the buffer should be the same") {
        REQUIRE(buffer.readOctetString(octetString.size()) == octetString);
      }
    }

    WHEN("the null terminated string is written to the buffer") {
      buffer.writeNullTerminatedString(nullTerminatedString);
      THEN(
          "the size of the buffer should corrsepond to the string size + 1 because of the null "
          "terminator") {
        REQUIRE(buffer.size() == std::string{nullTerminatedString}.size() + 1);
      }
      THEN("the string value read from the buffer should be the same") {
        REQUIRE(buffer.readNullTerminatedString() == nullTerminatedString);
      }
    }

    WHEN("a string is written as null terminated string to the buffer") {
      buffer.writeNullTerminatedString(octetString);
      THEN(
          "the size of the buffer should corrsepond to the string size + 1 because of the null "
          "terminator") {
        REQUIRE(buffer.size() == octetString.size() + 1);
      }
      THEN("the string value read from the buffer should be the same") {
        REQUIRE(buffer.readNullTerminatedString() == octetString);
      }
    }
  }
}

SCENARIO("Buffer reads and writes multiple values properly", "[buffer]") {
  GIVEN("A buffer") {
    smpp::Buffer buffer;
    AND_GIVEN("some values with different sizes") {
      constexpr char ch{'a'};
      constexpr uint8_t x8{26};
      constexpr uint16_t x16{1000};
      constexpr uint32_t x32{999'999'999};
      const std::string octetString{"just_a_test_octet_string"};  // 24 symbols
      constexpr char nullTerminatedString[] =
          "constString";  // 11 symbols without the null terminator '\0'

      WHEN("all the values are written to the buffer") {
        buffer.writeChar(ch);
        buffer.writeInt8(x8);
        buffer.writeInt16(x16);
        buffer.writeInt32(x32);
        buffer.writeOctetString(octetString);
        buffer.writeNullTerminatedString(nullTerminatedString);
        THEN("the size of the buffer should be 1 + 1 + 2 + 4 + 24 + 12 = 44 bytes") {
          REQUIRE(buffer.size() == 44);
        }
        THEN(
            "if we read them in the same order that we wrote them to the buffer, the values "
            "should "
            "be the same") {
          REQUIRE(buffer.readChar() == ch);
          REQUIRE(buffer.readInt8() == x8);
          REQUIRE(buffer.readInt16() == x16);
          REQUIRE(buffer.readInt32() == x32);
          REQUIRE(buffer.readOctetString(octetString.size()) == octetString);
          REQUIRE(buffer.readNullTerminatedString() == nullTerminatedString);
        }
      }
    }
  }
}

TEST_CASE("Buffer skips bytes correctly") {
  smpp::Buffer buffer;
  REQUIRE_FALSE(buffer.areThereBytesToRead());

  constexpr uint32_t x{999'999'999};
  constexpr uint32_t y{123'456'789};

  buffer.writeInt32(x);
  buffer.writeInt32(y);

  for (int i = 0; i < 8; i++) {
    REQUIRE(buffer.areThereBytesToRead());
    buffer.skip(1);
  }
  REQUIRE_FALSE(buffer.areThereBytesToRead());
}

TEST_CASE("Buffer reads correct value after skipping 4 bytes") {
  smpp::Buffer buffer;
  REQUIRE_FALSE(buffer.areThereBytesToRead());

  constexpr uint32_t x{999'999'999};
  constexpr uint32_t y{123'456'789};

  buffer.writeInt32(x);
  buffer.writeInt32(y);
  REQUIRE(buffer.size() == 8);
  CAPTURE(buffer.size());
  REQUIRE(buffer.areThereBytesToRead());
  buffer.skip(sizeof(uint32_t));
  REQUIRE(buffer.areThereBytesToRead());
  REQUIRE(buffer.readInt32() == y);
  REQUIRE_FALSE(buffer.areThereBytesToRead());
}

TEST_CASE("Buffer reads correct values after resetting the reading marker") {
  smpp::Buffer buffer;

  constexpr uint32_t x{999'999'999};
  constexpr uint32_t y{123'456'789};

  buffer.writeInt32(x);
  buffer.writeInt32(y);
  REQUIRE(buffer.areThereBytesToRead());
  buffer.skip(8);
  REQUIRE_FALSE(buffer.areThereBytesToRead());
  buffer.resetReadMarker();
  REQUIRE(buffer.areThereBytesToRead());
  REQUIRE(buffer.readInt32() == x);
  REQUIRE(buffer.readInt32() == y);
}
