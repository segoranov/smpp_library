#ifndef SMPP_EXCEPTIONS_H
#define SMPP_EXCEPTIONS_H

#include <exception>
#include <string>

namespace smpp {
/**
 * Exception thrown when there are SMPP protocol related issues.
 */
class SmppException : public std::exception {
 private:
  std::string m_strError;

 public:
  SmppException() : m_strError("Default SMPP exception") {}
  explicit SmppException(const std::string &strError) : m_strError{strError} {}
  virtual const char *what() const noexcept { return m_strError.c_str(); }
};

class InvalidSystemIdException : public SmppException {
 public:
  InvalidSystemIdException() : SmppException{} {}
  explicit InvalidSystemIdException(const std::string &message) : SmppException(message) {}
};

class InvalidPasswordException : public SmppException {
 public:
  InvalidPasswordException() : SmppException{} {}
  explicit InvalidPasswordException(const std::string &message) : SmppException(message) {}
};

class InvalidSourceAddressException : public SmppException {
 public:
  InvalidSourceAddressException() : SmppException{} {}

  explicit InvalidSourceAddressException(const std::string &message) : SmppException(message) {}
};

class InvalidDestinationAddressException : public SmppException {
 public:
  InvalidDestinationAddressException() : SmppException{} {}
  explicit InvalidDestinationAddressException(const std::string &message)
      : SmppException(message) {}
};

}  // namespace smpp
#endif  // SMPP_EXCEPTIONS_H