#include <unistd.h>

#include <thread>

#include "async_smpp_server.h"

const int max_length = 1000;

int main() {
  // START SMPP SERVER ON 7778
  boost::asio::io_context io_context;
  server s(io_context, 7778);
  std::thread t1{[&io_context]() { io_context.run(); }};
  std::cout << "Started server at port 7778\n";

  // SYNC CLIENT
  using boost::asio::ip::tcp;
  tcp::socket clientSocket(io_context);
  tcp::resolver resolver(io_context);
  boost::asio::connect(clientSocket, resolver.resolve("127.0.0.1", "7778"));
  std::cout << "Client connected succesfully to 127.0.0.1:7778\n";
  std::cout << "Client sending bind transmitter to server.\n";

  std::shared_ptr<smpp::BindTransmitter> bindTransmitterPdu = smpp::BindTransmitter::createEmpty();

  bindTransmitterPdu->setCommandLength(47);
  bindTransmitterPdu->setCommandStatus(0);
  bindTransmitterPdu->setSequenceNumber(1);
  bindTransmitterPdu->setSystemId("SMPP3TEST");
  bindTransmitterPdu->setPassword("secret08");
  bindTransmitterPdu->setSystemType("SUBMIT1");
  bindTransmitterPdu->setInterfaceVersion(0x50);
  bindTransmitterPdu->setAddrTon(0x01);
  bindTransmitterPdu->setAddrNpi(0x01);

  // client sending bind transmitter
  std::stringstream ss;
  bindTransmitterPdu->serialize(ss);
  boost::asio::write(
      clientSocket, boost::asio::buffer(ss.str().c_str(), bindTransmitterPdu->getCommandLength()));

  // receiving hopefully bind transmitter resp
  char reply[max_length];
  size_t reply_length = boost::asio::read(clientSocket, boost::asio::buffer(reply, 31));
  std::stringstream ss_reply{std::string{reply, 31}};
  auto replyPdu = smpp::Pdu::deserialize(ss);

  if (replyPdu->getCommandId() == smpp::constants::CMD_ID_BIND_TRANSMITTER_RESP &&
      replyPdu->getCommandLength() == 31) {
    std::cout << "Client received bind transmitter resp.\n";
  } else {
    std::cout << "Client did not receive bind transmitter resp properly...";
  }

  sleep(3);

  return 0;
}