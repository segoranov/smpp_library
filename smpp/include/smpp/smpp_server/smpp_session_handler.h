#ifndef SMPP_SESSION_HANDLER_H
#define SMPP_SESSION_HANDLER_H

#include <boost/asio.hpp>
#include <deque>
#include <memory>
#include <string>

namespace smpp {

class SmppSessionHandler : public std::enable_shared_from_this<SmppSessionHandler> {
 private:
  boost::asio::io_context& m_ioContext;
  boost::asio::ip::tcp::socket m_socket;
  boost::asio::io_context::strand m_writeStrand;
  std::deque<std::string> m_sendPacketQueue;

 public:
  SmppSessionHandler(boost::asio::io_context& ioContext);

  boost::asio::ip::tcp::socket& socket();

  void start();

 private:
  void readPduCommandLength();
  void readPdu(uint32_t nCommandLength);
  void readPduDone();
};

}  // namespace smpp

#endif