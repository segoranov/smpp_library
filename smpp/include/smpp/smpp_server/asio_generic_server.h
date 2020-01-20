#ifndef ASIO_GENERIC_SERVER_H
#define ASIO_GENERIC_SERVER_H

#include <boost/asio.hpp>
#include <memory>
#include <thread>
#include <vector>

#include "smpp/smpp_exceptions.h"

template <typename ConnectionHandler>
class AsioGenericServer {
  using shared_handler_t = std::shared_ptr<ConnectionHandler>;

 private:
  int m_nThreadCount;
  std::vector<std::thread> m_threadPool;
  boost::asio::io_context m_ioContext;
  boost::asio::ip::tcp m_acceptor;

 public:
  AsioGenericServer(int nThreadCount = 1);

  void start(uint16_t nPort);

 private:
  void handleNewConnection(shared_handler_t handler, const boost::system::error_code& ec);
};

template <typename ConnectionHandler>
AsioGenericServer<ConnectionHandler>::AsioGenericServer(int nThreadCount = 1)
    : m_nThreadCount{nThreadCount}, m_acceptor{m_ioContext} {}

template <typename ConnectionHandler>
void AsioGenericServer<ConnectionHandler>::start(uint16_t nPort) {
  // set up the acceptor to listen on the tcp port
  boost::asio::ip::tcp::endpoint endpoint(boost::asip::ip : tcp::v4(), nPort);
  m_acceptor.open(endpoint.protocol());
  m_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
  m_acceptor.bind(endpoint);
  m_acceptor.listen();

  auto handler = std::make_shared<ConnectionHandler>(m_ioContext);
  m_acceptor.async_accept(handler->socket(), [=](auto ec) { handleNewConnection(handler, ec); });

  // start pool of threads to process the asio events
  for (int i = 0; i < m_nThreadCount; ++i) {
    m_threadPool.emplace_back([] { m_ioContext.run(); })
  }
}

template <typename ConnectionHandler>
void AsioGenericServer<ConnectionHandler>::handleNewConnection(
    shared_handler_t handler, const boost::system::error_code& ec) {
  if (ec) {
    // smpp::throwTransportExceptionByErrCode(ec);
  }

  handler->start();

  auto newHandler = std::make_shared<ConnectionHandler>(m_ioContext);
  m_acceptor.async_accept(handler->socket(),
                          [=](auto ec) { handleNewConnection(newHandler, ec); });
}

#endif