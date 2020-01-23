#ifndef SUBMIT_MULTI_H
#define SUBMIT_MULTI_H

#include <iostream>
#include <optional>
#include <string>
#include <vector>

#include "smpp/pdu/base_submit.h"
#include "smpp/smpp_constants.h"

namespace smpp {

class SMEDestAddress {
 private:
  const uint8_t m_nDestFlag{smpp::constants::SME_FORMAT_DESTINATION_ADDRESS};
  uint8_t m_nDestAddrTon;
  uint8_t m_nDestAddrNpi;
  std::string m_strDestinationAddr;

 public:
  explicit SMEDestAddress(uint8_t nDestAddrTon, uint8_t nDestAddrNpi,
                          const std::string& strDestinationAddr);
  SMEDestAddress& operator=(const SMEDestAddress& other);

  uint8_t getDestAddrTon() const;
  uint8_t getDestAddrNpi() const;
  std::string getDestinationAddr() const;

  int size() const;

  friend bool operator==(const SMEDestAddress& lhs, const SMEDestAddress& rhs);
  friend bool operator!=(const SMEDestAddress& lhs, const SMEDestAddress& rhs);
};

class DistributionListDestAddress {
 private:
  const uint8_t m_nDestFlag{smpp::constants::DISTRIBUTION_LIST_FORMAT_DESTINATION_ADDRESS};
  std::string m_strDlName;

 public:
  explicit DistributionListDestAddress(const std::string& strDlName);
  DistributionListDestAddress& operator=(const DistributionListDestAddress& other);

  std::string getDlName() const;

  int size() const;

  friend bool operator!=(const DistributionListDestAddress& lhs,
                         const DistributionListDestAddress& rhs);
  friend bool operator==(const DistributionListDestAddress& lhs,
                         const DistributionListDestAddress& rhs);
};

class SubmitMultiDestinationAddresses {
 private:
  uint8_t m_nNumberOfDests{0};
  std::vector<SMEDestAddress> m_vSMEDestAddresses;
  std::vector<DistributionListDestAddress> m_vDistributionListDestAddresses;

 public:
  uint8_t getNumberOfDests() const;
  std::vector<SMEDestAddress> getSMEDestAddresses() const;
  std::vector<DistributionListDestAddress> getDistributionListDestAddresses() const;

  void addSMEDestAddress(const SMEDestAddress& addr);
  void addDistributionListDestAddress(const DistributionListDestAddress& addr);

  int size() const;

  std::string toString() const;

  void serialize(std::ostream& os) const;
  void deserialize(std::istream& is);

  friend bool operator==(const SubmitMultiDestinationAddresses& lhs,
                         const SubmitMultiDestinationAddresses& rhs);
  friend bool operator!=(const SubmitMultiDestinationAddresses& lhs,
                         const SubmitMultiDestinationAddresses& rhs);
};

namespace builder {
class SubmitMultiBuilder;
}

class SubmitMulti final : public BaseSubmit {
 private:
  SubmitMulti();

  SubmitMultiDestinationAddresses m_destinationAddresses;

 private:
  friend const std::unordered_map<uint32_t, Pdu::Factory>& getCommandIdToFactoryMap();
  static std::unique_ptr<SubmitMulti> create(std::istream& is);

 public:
  explicit SubmitMulti(const builder::SubmitMultiBuilder& params);

  virtual void serialize(std::ostream& os) const override;

  SubmitMultiDestinationAddresses getDestinationAddresses() const;
};

}  // namespace smpp

#endif