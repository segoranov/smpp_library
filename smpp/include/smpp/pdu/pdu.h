#ifndef PDU_H
#define PDU_H

#include <functional>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <unordered_map>

#include "smpp/smpp_constants.h"
#include "smpp/smpp_exceptions.h"
#include "smpp/tlv/tlv.h"
#include "smpp/util/smpp_util.h"

namespace smpp {

class SubmitSm;
class SubmitSmResp;

class DeliverSm;
class DeliverSmResp;

class DataSm;
class DataSmResp;

class SubmitMulti;
class SubmitMultiResp;

template <uint32_t CommandId>
class Bind;

using BindTransmitter = Bind<constants::CMD_ID_BIND_TRANSMITTER>;

template <uint32_t CommandId>
class BindResp;

using BindTransmitterResp = BindResp<constants::CMD_ID_BIND_TRANSMITTER_RESP>;

class Outbind;

/**
 * Base class for all SMPP PDUs
 *
 * For serialization/deserialization, the design described here is used:
 * https://isocpp.org/wiki/faq/serialization#serialize-inherit-no-ptrs
 * with the Named Constructor Idiom
 */
class Pdu : public std::enable_shared_from_this<Pdu> {
 protected:
  // PDU Header
  uint32_t m_nCommandLength;
  uint32_t m_nCommandId;
  uint32_t m_nCommandStatus;
  uint32_t m_nSequenceNumber;

  std::vector<Tlv> m_vOptionalTlvParameters;

  explicit Pdu(uint32_t nCommandId);

 public:
  // Aliases for convenience
  using UPtr = std::unique_ptr<Pdu>;
  using SPtr = std::shared_ptr<Pdu>;
  using WPtr = std::weak_ptr<Pdu>;

  uint32_t getCommandLength() const;
  uint32_t getCommandId() const;
  uint32_t getCommandStatus() const;
  uint32_t getSequenceNumber() const;
  std::vector<Tlv> getOptionalParameters() const;

  bool hasOptionalParameter(uint16_t nTag) const;

  std::shared_ptr<SubmitSm> asSubmitSm();
  std::shared_ptr<DeliverSm> asDeliverSm();
  std::shared_ptr<BindTransmitter> asBindTransmitter();
  std::shared_ptr<BindTransmitterResp> asBindTransmitterResp();
  std::shared_ptr<SubmitMulti> asSubmitMulti();
  std::shared_ptr<SubmitSmResp> asSubmitSmResp();
  std::shared_ptr<Outbind> asOutbind();
  std::shared_ptr<DataSm> asDataSm();

  /**
   * @brief Compare two PDUs
   *
   * @return true if they are of the same type and have equal fields; false otherwise
   */
  virtual bool equals(const Pdu& other) const;

  /**
   * @brief Serializes a PDU by writing raw bytes to an output stream
   */
  virtual void serialize(std::ostream& os) const = 0;

  /**
   * @brief Deserializes and creates a PDU by reading raw bytes from an input stream
   */
  static UPtr deserialize(std::istream& is);

 protected:
  /**
   * This function will be present in each concrete SMPP message class,
   * for example BindTransceiver, BindTransmitterResp and so on...
   *
   * The purpose of the function is to deserialize the PDU body based
   * on the PDU command id
   */
  using Factory = std::function<UPtr(std::istream& is)>;

  // Utility methods for serialization/deserialization
  void serializeHeader(std::ostream& os) const;
  void serializeOptionalParameters(std::ostream& os) const;
  void deserializeOptionalParameters(std::istream& is);
};

}  // namespace smpp

#endif