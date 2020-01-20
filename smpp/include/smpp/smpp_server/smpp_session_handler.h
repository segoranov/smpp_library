#ifndef SMPP_SESSION_HANDLER_H
#define SMPP_SESSION_HANDLER_H

#include <boost/asio.hpp>
#include <deque>
#include <memory>
#include <string>

#include "smpp/pdu/pdu.h"

namespace smpp {

class SmppSessionHandler : public std::enable_shared_from_this<SmppSessionHandler> {
 private:
  boost::asio::io_context& m_ioContext;
  boost::asio::ip::tcp::socket m_socket;
  boost::asio::io_context::strand m_writeStrand;
  std::deque<smpp::Pdu::Ptr> m_sendPduQueue;

 public:
  SmppSessionHandler(boost::asio::io_context& ioContext);

  boost::asio::ip::tcp::socket& socket();

  void start();

 private:
  void readPduCommandLength();
  void readPdu(uint32_t nCommandLength);
  void readPduDone();

  void sendPdu(smpp::Pdu::Ptr pdu);
  void queuePdu(smpp::Pdu::Ptr pdu);
  void startPduSend();
  void pduSendDone(const boost::system::error_code& ec);
};

}  // namespace smpp

#endif