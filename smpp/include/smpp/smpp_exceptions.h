#ifndef SMPP_EXCEPTIONS_H
#define SMPP_EXCEPTIONS_H

#include <boost/asio/error.hpp>
#include <exception>
#include <sstream>
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

class InvalidTagException : public SmppException {
 public:
  InvalidTagException() : SmppException{"Invalid tag"} {}
  explicit InvalidTagException(const std::string& strError) : SmppException{strError} {}
};

class InvalidInterfaceVersionException : public SmppException {
 public:
  InvalidInterfaceVersionException() : SmppException{"Invalid interface version"} {}
  explicit InvalidInterfaceVersionException(const std::string& strError)
      : SmppException{strError} {}
};

class InvalidFieldException : public SmppException {
 public:
  InvalidFieldException() : SmppException{"Invalid interface version"} {}
  explicit InvalidFieldException(const std::string& strError)
      : SmppException{strError} {}
};

class UndefinedValueException : public SmppException {
 public:
  UndefinedValueException() : SmppException{"Undefined value"} {}
  explicit UndefinedValueException(const std::string& strError) : SmppException{strError} {}
};

class InvalidSessionStateException : public SmppException {
 public:
  InvalidSessionStateException() : SmppException{"Invalid session state"} {}
  explicit InvalidSessionStateException(const std::string& strError) : SmppException{strError} {}
};

class FieldOutOfRangeException : public SmppException {
 public:
  FieldOutOfRangeException() : SmppException{"Field out of range exception"} {}
  explicit FieldOutOfRangeException(const std::string& strError) : SmppException{strError} {}
};

/**
 * Exception thrown when there are TCP connection related issues
 */
class TransportException : public std::exception {
 private:
  std::string m_strError;

 public:
  TransportException() : m_strError("Default transport exception") {}
  explicit TransportException(const std::string& strError) : m_strError{strError} {}
  virtual const char* what() const noexcept override { return m_strError.c_str(); }
};

}  // namespace smpp

#endif  // SMPP_EXCEPTIONS_H