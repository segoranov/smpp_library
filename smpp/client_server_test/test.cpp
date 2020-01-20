#include <unistd.h>

#include <boost/asio.hpp>
#include <thread>

#include "smpp/pdu/bind.h"
#include "smpp/pdu/builder/bind_builder.h"
#include "smpp/smpp_server/smpp_server.h"
#include "smpp/util/logging.h"

const int max_length = 1000;

int main() {
  INFO << __FUNCTION__ << ": Starting test.";
  INFO << "PROGRAM STARTED.";

  // START SMPP SERVER ON 7778
  smpp::SmppServer smppServer;
  smppServer.start(7778);
  INFO << "Started server at port 7778\n";

  // SYNC CLIENT
  using boost::asio::ip::tcp;
  boost::asio::io_context io_context;
  tcp::socket clientSocket(io_context);
  tcp::resolver resolver(io_context);
  boost::asio::connect(clientSocket, resolver.resolve("127.0.0.1", "7778"));
  INFO << "Client connected succesfully to 127.0.0.1:7778\n";
  INFO << "Client sending bind transmitter to server.\n";

  smpp::BindTransmitter bindTransmitterPdu{
      smpp::builder::BindBuilder()
          .withCommandLength(47)
          .withCommandStatus(smpp::constants::errors::ESME_ROK)
          .withSequenceNumber(1)
          .withSystemId("SMPP3TEST")
          .withPassword("secret08")
          .withSystemType("SUBMIT1")
          .withInterfaceVersion(0x50)
          .withAddrTon(0x01)
          .withAddrNpi(0x01)
          .withAddressRange(smpp::constants::null_settings::NULL_C_OCTET_STRING)};

  // client sending bind transmitter
  std::stringstream ss;
  bindTransmitterPdu.serialize(ss);
  boost::asio::write(clientSocket,
                     boost::asio::buffer(ss.str().c_str(), bindTransmitterPdu.getCommandLength()));

  // receiving hopefully bind transmitter resp
  char reply[max_length];
  size_t reply_length = boost::asio::read(clientSocket, boost::asio::buffer(reply, 31));
  std::stringstream ss_reply{std::string{reply, 31}};
  auto replyPdu = smpp::Pdu::deserialize(ss);

  if (replyPdu->getCommandId() == smpp::constants::CMD_ID_BIND_TRANSMITTER_RESP) {
    INFO << "Client received bind transmitter resp.\n";
  } else {
    INFO << "Client did not receive bind transmitter resp properly...";
  }

  sleep(15);

  return 0;
}