#ifndef DATA_SM_H
#define DATA_SM_H

#include "smpp/pdu/pdu.h"

namespace smpp {

namespace builder {
class DataSmBuilder;
}

class DataSm final : public Pdu {
 private:
  DataSm();

  std::string m_strServiceType;
  uint8_t m_nSourceAddrTon;
  uint8_t m_nSourceAddrNpi;
  std::string m_strSourceAddr;
  uint8_t m_nDestAddrTon;
  uint8_t m_nDestAddrNpi;
  std::string m_strDestinationAddr;
  uint8_t m_nEsmClass;
  uint8_t m_nRegisteredDelivery;
  uint8_t m_nDataCoding;

 private:
  friend const std::unordered_map<uint32_t, Pdu::Factory>& getCommandIdToFactoryMap();
  static std::unique_ptr<DataSm> create(std::istream& is);

 public:
  explicit DataSm(const builder::DataSmBuilder& params);

  virtual void serialize(std::ostream& os) const override;

  std::string getServiceType() const;
  uint8_t getSourceAddrTon() const;
  uint8_t getSourceAddrNpi() const;
  std::string getSourceAddr() const;
  uint8_t getDestAddrTon() const;
  uint8_t getDestAddrNpi() const;
  std::string getDestinationAddr() const;
  uint8_t getEsmClass() const;
  uint8_t getRegisteredDelivery() const;
  uint8_t getDataCoding() const;

  virtual bool equals(const Pdu& other) const override;
};

}  // namespace smpp

#endif