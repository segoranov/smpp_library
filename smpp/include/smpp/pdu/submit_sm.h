#ifndef SUBMIT_SM_H
#define SUBMIT_SM_H

#include "smpp/pdu/base_submit.h"

namespace smpp {

namespace builder {
class SubmitSmBuilder;
}

class SubmitSm final : public BaseSubmit {
 private:
  SubmitSm();

  uint8_t m_nDestAddrTon;
  uint8_t m_nDestAddrNpi;
  std::string m_strDestinationAddr;

 private:
  friend const std::unordered_map<uint32_t, Pdu::Factory>& getCommandIdToFactoryMap();
  static std::unique_ptr<SubmitSm> create(std::istream& is);

 public:
  explicit SubmitSm(const builder::SubmitSmBuilder& params);

  virtual void serialize(std::ostream& os) const override;

  uint8_t getDestAddrTon() const;
  uint8_t getDestAddrNpi() const;
  std::string getDestinationAddr() const;

  virtual bool equals(const Pdu& other) const override;
};

}  // namespace smpp

#endif