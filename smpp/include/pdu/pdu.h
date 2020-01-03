#ifndef PDU_H
#define PDU_H

#include <arpa/inet.h>

#include <cereal/access.hpp>
#include <functional>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <unordered_map>

#include "smpp_constants.h"
#include "smpp_exceptions.h"
#include "tlv/tlv.h"
#include "util/smpp_util.h"

namespace smpp {

class Pdu {
 protected:
  // PDU Header
  uint32_t m_nCommandLength;
  uint32_t m_nCommandId;
  uint32_t m_nCommandStatus;
  uint32_t m_nSequenceNumber;

  std::vector<Tlv> m_vOptionalTlvParameters;

  const bool m_bIsRequest;

 public:
  /**
   * @throw InvalidCommandIdException if the given command id is invalid
   */
  explicit Pdu(uint32_t nCommandId, bool bIsRequest);

  uint32_t getCommandLength() const;
  uint32_t getCommandId() const;
  uint32_t getCommandStatus() const;
  uint32_t getSequenceNumber() const;
  std::vector<Tlv> getOptionalParameters() const;

  bool hasOptionalParameter(uint16_t nTag) const;

  bool isRequest() const;
  bool isResponse() const;

  // -------------------------------------------
  // ------ SERIALIZATION/DESERIALIZATION ------

  /**
   * Using the serialization design described here:
   * https://isocpp.org/wiki/faq/serialization#serialize-inherit-no-ptrs
   * with the Named Constructor Idiom
   */

  virtual void serialize(std::ostream& os) const = 0;
  static std::unique_ptr<Pdu> deserialize(std::istream& is);

  /**
   * This function will be present in each concrete SMPP message class,
   * for example BindTransceiver, BindTransmitterResp and so on...
   *
   * The purpose of the function is to deserialize the PDU body based
   * on the type of SMPP message
   */
  using BodyFactory = std::function<std::unique_ptr<Pdu>(std::istream& is)>;

 protected:
  /**
   * Utility methods for serialization/deserialization
   */

  virtual void serializeBody(std::ostream& os) const = 0;
  virtual void deserializeBody(std::istream& is) = 0;

  void serializeHeader(std::ostream& os) const;
  void serializeOptionalParameters(std::ostream& os) const;
};

}  // namespace smpp

#endif