#include <memory>

#include "smpp/commands.h"
#include "smpp/smpp_client.h"

int main() {
  boost::asio::io_context io_context;
  auto tcpSocketPtr = std::make_shared<boost::asio::ip::tcp::socket>(io_context);
  boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"),
                                          2775);
  tcpSocketPtr->connect(endpoint);
  smpp::SmppClient smppClient{tcpSocketPtr};

  auto bindResp = smppClient.bind(smpp::BindTransmitter{
      smpp::builder::BindBuilder()
          .withCommandStatus(smpp::constants::errors::ESME_ROK)
          .withSequenceNumber(1)
          .withSystemId("SMPP3TEST")
          .withPassword("secret08")
          .withSystemType("test_system_type")
          .withInterfaceVersion(0x50)
          .withAddrTon(0x01)
          .withAddrNpi(0x01)
          .withAddressRange(smpp::constants::null_settings::NULL_C_OCTET_STRING)});

  auto bindTransmitterResp = bindResp->asBindTransmitterResp();

  io_context.run();
  std::cout << "Bound with status " << bindTransmitterResp->getCommandStatus() << std::endl;
  std::cout << "Bind response sequence number: " << bindTransmitterResp->getSequenceNumber()
            << std::endl;
}
