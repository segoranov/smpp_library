

#include <iostream>
#include <memory>

#include "aliases.h"
#include "catch.hpp"
#include "pdu/bindtransmitter.h"
#include "pdu/pdu.h"
#include "smppconstants.h"
#include "transcoder/pdu_transcoder.h"

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
        REQUIRE(buffer.readString(octetString.size()) == octetString);
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
  GIVEN("A buffer and some values with different sizes") {
    smpp::Buffer buffer;
    constexpr char ch{'a'};
    constexpr uint8_t x8{26};
    constexpr uint16_t x16{1000};
    constexpr uint32_t x32{999'999'999};
    const std::string octetString{"just_a_test_octet_string"};
    constexpr char nullTerminatedString[] = "constString";

    WHEN("all the values are written to the buffer") {
      buffer.writeChar(ch);
      buffer.writeInt8(x8);
      buffer.writeInt16(x16);
      buffer.writeInt32(x32);
      buffer.writeOctetString(octetString);
      buffer.writeNullTerminatedString(nullTerminatedString);
      THEN(
          "if we read them in the same order that we wrote them to the buffer, the values should "
          "be the same") {
        REQUIRE(buffer.readChar() == ch);
        REQUIRE(buffer.readInt8() == x8);
        REQUIRE(buffer.readInt16() == x16);
        REQUIRE(buffer.readInt32() == x32);
        REQUIRE(buffer.readString(octetString.size()) == octetString);
        REQUIRE(buffer.readNullTerminatedString() == nullTerminatedString);
      }
    }
  }
}

TEST_CASE("Pdu header is encoded properly in buffer", "[pdu_header]") {
  /*
  Sample PDU (Values are shown in Hex format):
  00 00 00 2F 00 00 00 02 00 00 00 00 00 00 00 01
  53 4D 50 50 33 54 45 53 54 00 73 65 63 72 65 74
  30 38 00 53 55 42 4D 49 54 31 00 50 01 01 00

  The 16-octet header would be decoded as follows:
  00 00 00 2F Command Length 0x0000002F
  00 00 00 02 Command ID 0x00000002
  00 00 00 00 Command Status 0x00000000
  00 00 00 01 Sequence Number 0x00000001
  */
  const char samplePduHeader[] = {0x00, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00, 0x02,
                                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};

  std::unique_ptr<smpp::Pdu> pdu = std::make_unique<smpp::BindTransmitter>();
  pdu->setCommandLength(47);  // 0x0000002F in hex is 47 in decimal
  pdu->setCommandStatus(0);   // 0x00000000
  pdu->setSequenceNumber(1);  // 0x00000001

  smpp::Buffer buffer;
  pdu->writeHeader(buffer);
  std::cout << buffer.size() << std::endl;

  std::cout << "Buf:\n";
  for (int i = 0; i < 16; i++) {
    printf("0x%.2x ", buffer.toString()[i]);
  }

  std::cout << std::endl;

  std::cout << "PduHeader:\n";
  for (int i = 0; i < 16; i++) {
    printf("0x%.2x ", samplePduHeader[i]);
  }

  std::cout << std::endl;

  // TODO SG: Fix this test!
  REQUIRE(buffer.toString() == samplePduHeader);
}
