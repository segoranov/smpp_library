#ifndef SMPP_SESSION_HANDLER_H
#define SMPP_SESSION_HANDLER_H

#include <boost/asio.hpp>
#include <deque>
#include <list>
#include <memory>
#include <string>

#include "smpp/commands.h"
#include "smpp/util/smpp_session_util.h"

namespace smpp {

class SmppSessionHandler : public std::enable_shared_from_this<SmppSessionHandler> {
 private:
  boost::asio::io_context& m_ioContext;
  boost::asio::ip::tcp::socket m_socket;
  boost::asio::io_context::strand m_writeStrand;
  std::deque<std::string> m_sendPduQueue;
  std::list<Pdu::Ptr> m_receivePduQueue;
  std::atomic<session_util::SessionState> m_enSessionState;

 public:
  SmppSessionHandler(boost::asio::io_context& ioContext);

  boost::asio::ip::tcp::socket& socket();

  void start();

 private:
  void readPdu();
  void readPduCommandLength();
  void readPduAfterCommandLength(uint32_t nCommandLength);
  void onReceivedPdu(Pdu::Ptr pdu);

  void onReceivedBindTransmitter(Pdu::Ptr pdu);

  void sendPdu(const std::string& strPdu);
  void queuePdu(const std::string& strPdu);
  void startPduSend();
  void pduSendDone(const boost::system::error_code& ec);
};

}  // namespace smpp

#endif