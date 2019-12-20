#include "util/smpp_util.h"

#include "catch.hpp"
#include "smppconstants.h"
#include "smppexceptions.h"

SCENARIO("Creating PDU given a command id") {
  WHEN("Trying to create a PDU with invalid command id") {
    THEN("InvalidCommandIdException must be thrown") {
      REQUIRE_THROWS_AS(smpp::util::createPduByCommandId(696923412),
                        smpp::InvalidCommandIdException);
    }

    WHEN("Trying to create a PDU with command id BindTransmitter") {
      THEN("No exception should be thrown") {
        REQUIRE_NOTHROW(
            smpp::util::createPduByCommandId(smpp::constants::CMD_ID_BIND_TRANSMITTER));
      }
    }
  }
}
