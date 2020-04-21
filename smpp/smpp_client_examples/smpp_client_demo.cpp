#include <memory>

#include "smpp/commands.h"
#include "smpp/smpp_client.h"

/**
 * Demonstrates only synchronous communication - client
 * sends a PDU and blocks waiting for PDU response
 */
void syncClientDemo() {
  boost::asio::io_context io_context;
  auto tcpSocketPtr = std::make_shared<boost::asio::ip::tcp::socket>(io_context);
  boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"),
                                          2775);
  tcpSocketPtr->connect(endpoint);
  smpp::SmppClient smppClient{tcpSocketPtr};

  auto bindResp = smppClient.bind(smpp::BindTransmitter{
      smpp::builder::BindBuilder()
          .withSequenceNumber(1)
          .withSystemId("SMPP3TEST")
          .withPassword("secret08")
          .withSystemType("test_system_type")
          .withInterfaceVersion(0x50)
          .withAddrTon(0x01)
          .withAddrNpi(0x01)
          .withAddressRange(smpp::constants::null_settings::NULL_C_OCTET_STRING)});

  auto bindTransmitterResp = bindResp->asBindTransmitterResp();

  std::cout << "Bound with status " << bindTransmitterResp->getCommandStatus() << std::endl;
  std::cout << "Bind response sequence number: " << bindTransmitterResp->getSequenceNumber()
            << std::endl;

  std::cout << "Sending submit sm with message \"TEST_SM\"" << std::endl;
  auto submitResp = smppClient.sendPduSync(std::make_shared<smpp::SubmitSm>(smpp::SubmitSm{
      smpp::builder::SubmitSmBuilder()
          .withSequenceNumber(2)
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
          .withShortMessage("TEST_SM")}));

  auto submitSmResp = submitResp->asSubmitSmResp();
  std::cout << "Received submit sm response with status " << submitResp->getCommandStatus()
            << std::endl;

  smppClient.unbind();
}

int main() { syncClientDemo(); }
