#include <chrono>
#include <iostream>
#include <sstream>

#include "smpp/commands.h"

using namespace std;
using Time = std::chrono::steady_clock;
using ms = std::chrono::milliseconds;
using float_sec = std::chrono::duration<float>;
using float_time_point = std::chrono::time_point<Time, float_sec>;

float_time_point getCurrentTime() { return Time::now(); }

smpp::SubmitSm createTestPdu() {
  return smpp::SubmitSm{
      smpp::builder::SubmitSmBuilder()
          .withCommandStatus(smpp::constants::errors::ESME_ROK)
          .withSequenceNumber(378019)
          .withServiceType("A")
          .withSourceAddrTon(0x03)
          .withSourceAddrNpi(0x01)
          .withSourceAddr("B")
          .withDestAddrTon(0x03)
          .withDestAddrNpi(0x01)
          .withDestinationAddr("C")
          .withEsmClass(smpp::constants::null_settings::NULL_INT8)
          .withProtocolId(smpp::constants::null_settings::NULL_INT8)
          .withPriorityFlag(smpp::constants::null_settings::NULL_INT8)
          .withScheduleDeliveryTime(smpp::constants::null_settings::NULL_C_OCTET_STRING)
          .withValidityPeriod("D")
          .withRegisteredDelivery(0x01)
          .withReplaceIfPresentFlag(smpp::constants::null_settings::NULL_INT8)
          .withDataCoding(smpp::constants::null_settings::NULL_INT8)
          .withSmDefaultMsgId(smpp::constants::null_settings::NULL_INT8)
          .withShortMessage(
              "SIMPLE_SHORT_MESSAGE_FOR_SUBMIT_SM_PDU_WITH_SOME_SYMBOLS_INSIDE_OF_IT")};
}

/** Tests how many PDUs can be serialized for a number of seconds
 *
 */
void doPerformanceTest(float seconds) {
  std::cout << "\n--------------------------------------\n";
  int countSerializedPDUs = 0;
  smpp::SubmitSm testPdu = createTestPdu();
  std::cout << "Starting test with PDU of size " << testPdu.getCommandLength() << " for "
            << seconds << " seconds..." << std::endl;
  stringstream ss;

  auto startTime = getCurrentTime();

  while ((getCurrentTime() - startTime).count() < seconds) {
    testPdu.serialize(ss);
    ++countSerializedPDUs;
  }

  auto timeAfterStart = (getCurrentTime() - startTime).count();
  std::cout << "Time passed: " << timeAfterStart
            << " seconds. PDUs serialized: " << countSerializedPDUs << "." << std::endl;

  std::cout << countSerializedPDUs << " / " << timeAfterStart << " = "
            << countSerializedPDUs / timeAfterStart << " serialized PDUs per second." << std::endl;

  std::cout << "Stream size: " << ss.str().size() << " bytes." << std::endl;
  std::cout << "--------------------------------------\n\n";
}

int main() {
  doPerformanceTest(1);
  doPerformanceTest(10);
}