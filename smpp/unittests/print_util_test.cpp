#include "catch.hpp"
#include "util/print_util.h"

TEST_CASE("toHexString() returns proper string") {
    REQUIRE(smpp::print_util::toHexString(45123) == "0xB043");
}