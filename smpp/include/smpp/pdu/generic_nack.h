#ifndef GENERIC_NACK_H
#define GENERIC_NACK_H

#include "smpp/pdu/pdu.h"

namespace smpp {

namespace builder {
class GenericNackBuilder;
}

class GenericNack final : public Pdu {
 private:
  GenericNack();

  friend const std::unordered_map<uint32_t, Pdu::Factory>& getCommandIdToFactoryMap();
  static std::unique_ptr<GenericNack> create(std::istream& is);

 public:
  explicit GenericNack(const builder::GenericNackBuilder& params);

  virtual void serialize(std::ostream& os) const override;

  virtual bool equals(const Pdu& other) const override;
};

}  // namespace smpp

#endif
