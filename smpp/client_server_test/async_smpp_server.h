#include <boost/asio.hpp>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>

#include "pdu/bind_transmitter.h"
#include "pdu/bind_transmitter_resp.h"
#include "pdu/builder/bind_transmitter_resp_builder.h"
#include "smpp_constants.h"

using boost::asio::ip::tcp;

class session : public std::enable_shared_from_this<session> {
 public:
  session(tcp::socket socket) : socket_(std::move(socket)) {}

  void start() { do_read(); }

 private:
  void do_read() {
    auto self(shared_from_this());
    socket_.async_read_some(
        boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length) {
          if (!ec) {
            std::stringstream ssRecv{std::string{data_, length}};
            auto pdu = smpp::Pdu::deserialize(ssRecv);
            if (!pdu->getCommandId() == smpp::constants::CMD_ID_BIND_TRANSCEIVER) {
              throw "Server expecting bind transmitter...";
            }
            std::cout << "Server received bind transmitter\n";
            std::cout << "Server sending bind transmitter resp...\n";

            std::stringstream ssSend;
            auto bindTransmitterRespPdu =
                smpp::builder::BindTransmitterRespBuilder::BindTransmitterRespPdu()
                    .withCommandLength(31)
                    .withCommandStatus(0)
                    .withSequenceNumber(0)
                    .withSystemId("SMPP3TEST")
                    .withOptionalParameter(smpp::Tlv{smpp::constants::TAG_SC_INTERFACE_VERSION,
                                                     static_cast<uint8_t>(0x01)})
                    .build();

            bindTransmitterRespPdu->serialize(ssSend);
            boost::asio::async_write(
                socket_,
                boost::asio::buffer(ssSend.str().c_str(),
                                    bindTransmitterRespPdu->getCommandLength()),
                [this, self](boost::system::error_code ec, std::size_t /*length*/) {
                  if (!ec) {
                    std::cout
                        << "Server closing connection after sending bind transmitter resp...\n";
                  }
                });
          }
        });
  }

  void do_write(std::size_t length) {
    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
                             [this, self](boost::system::error_code ec, std::size_t /*length*/) {
                               if (!ec) {
                                 do_read();
                               }
                             });
  }

  tcp::socket socket_;
  enum { max_length = 1024 };
  char data_[max_length];
};

class server {
 public:
  server(boost::asio::io_context& io_context, short port)
      : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
    do_accept();
  }

 private:
  void do_accept() {
    acceptor_.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
      if (!ec) {
        std::cout << "Server accepted new connection...\n";
        std::make_shared<session>(std::move(socket))->start();
      }

      do_accept();
    });
  }

  tcp::acceptor acceptor_;
};
