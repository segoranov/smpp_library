#ifndef SMPP_EXCEPTIONS_H
#define SMPP_EXCEPTIONS_H

#include <stdexcept>
#include <string>

namespace smpp {
/**
 * Exception thrown when there are SMPP protocol related issues.
 */
class SmppException : public std::runtime_error {
 public:
  SmppException() : std::runtime_error("Default SmppException.") {}
  explicit SmppException(const std::string &message) : std::runtime_error(message) {}
};

class InvalidSystemIdException : public SmppException {
 public:
  InvalidSystemIdException() : SmppException() {}

  explicit InvalidSystemIdException(const std::string &message) : SmppException(message) {}
};

class InvalidPasswordException : public SmppException {
 public:
  InvalidPasswordException() : SmppException() {}
  explicit InvalidPasswordException(const std::string &message) : SmppException(message) {}
};

class InvalidSourceAddressException : public SmppException {
 public:
  InvalidSourceAddressException() : SmppException() {}

  explicit InvalidSourceAddressException(const std::string &message) : SmppException(message) {}
};

class InvalidDestinationAddressException : public SmppException {
 public:
  InvalidDestinationAddressException() : SmppException() {}
  explicit InvalidDestinationAddressException(const std::string &message)
      : SmppException(message) {}
};

/**
 * Exception thrown when there is transport/connection related issues.
 */
class TransportException : public std::runtime_error {
 public:
  TransportException() : std::runtime_error("Default TransportException.") {}
  explicit TransportException(const std::string &message) : std::runtime_error(message) {}
};
}  // namespace smpp
#endif  // SMPP_EXCEPTIONS_H