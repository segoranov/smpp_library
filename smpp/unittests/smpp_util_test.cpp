#include "util/smpp_util.h"

#include "catch.hpp"
#include "smpp_constants.h"

TEST_CASE("Tag 0x7789 should be invalid") { REQUIRE_FALSE(smpp::util::isTlvTagValid(0x7789)); }

TEST_CASE("Tag 0x0304, corresponding to TAG_NUMBER_OF_MESSAGES, should be valid") {
  REQUIRE(smpp::util::isTlvTagValid(0x0304));
  REQUIRE(smpp::util::isTlvTagValid(smpp::constants::TAG_NUMBER_OF_MESSAGES));
}

TEST_CASE("Command ID 0x7789AABB should be invalid") {
  REQUIRE_FALSE(smpp::util::isCommandIdValid(0x7789AABB));
}

TEST_CASE("Tag 0x80000000, corresponding to CMD_ID_GENERIC_NACK, should be valid") {
  REQUIRE(smpp::util::isCommandIdValid(0x80000000));
  REQUIRE(smpp::util::isCommandIdValid(smpp::constants::CMD_ID_GENERIC_NACK));
}
