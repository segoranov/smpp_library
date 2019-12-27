#include "util/smpp_util.h"

#include "catch.hpp"
#include "smppconstants.h"

TEST_CASE("Tag 0x7789 should be invalid") { REQUIRE_FALSE(smpp::util::isTlvTagValid(0x7789)); }

TEST_CASE("Tag 0x0304, correspondingto TAG_NUMBER_OF_MESSAGES, should be valid") {
  REQUIRE(smpp::util::isTlvTagValid(0x0304));
  REQUIRE(smpp::util::isTlvTagValid(smpp::constants::TAG_NUMBER_OF_MESSAGES));
}