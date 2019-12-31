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
  explicit SmppException(const std::string& strError) : m_strError{strError} {}
  virtual const char* what() const noexcept override { return m_strError.c_str(); }
};

class InvalidCommandIdException : public SmppException {
 public:
  InvalidCommandIdException() : SmppException{"Invalid command id"} {}
  explicit InvalidCommandIdException(const std::string& strError) : SmppException{strError} {}
};

class InvalidCommandLengthException : public SmppException {
 public:
  InvalidCommandLengthException() : SmppException{"Invalid command length"} {}
  explicit InvalidCommandLengthException(const std::string& strError) : SmppException{strError} {}
};

class InvalidSystemIdException : public SmppException {
 public:
  InvalidSystemIdException() : SmppException{"Invalid system id"} {}
  explicit InvalidSystemIdException(const std::string& strError) : SmppException{strError} {}
};

class InvalidPasswordException : public SmppException {
 public:
  InvalidPasswordException() : SmppException{"Invalid password"} {}
  explicit InvalidPasswordException(const std::string& strError) : SmppException{strError} {}
};

class InvalidSourceAddressException : public SmppException {
 public:
  InvalidSourceAddressException() : SmppException{"Invalid source address"} {}
  explicit InvalidSourceAddressException(const std::string& strError) : SmppException{strError} {}
};

class InvalidDestinationAddressException : public SmppException {
 public:
  InvalidDestinationAddressException() : SmppException{"Invalid destination address"} {}
  explicit InvalidDestinationAddressException(const std::string& strError)
      : SmppException{strError} {}
};

/**
 * Thrown when an unrecoverable PDU decoding error occurs. A good example is
 * a command length which is less than 16 (the mandatory PDU header length)
 *
 * Another example is an invalid sequence number in an invalid range.
 *
 * The recommended action for an unrecoverable error is to close the SMPP
 * connection.
 */
class UnrecoverablePduException : public SmppException {
 public:
  UnrecoverablePduException() : SmppException{"Unrecoverable pdu"} {}
  explicit UnrecoverablePduException(const std::string& strError) : SmppException{strError} {}
};

}  // namespace smpp
#endif  // SMPP_EXCEPTIONS_H