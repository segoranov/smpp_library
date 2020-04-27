#ifndef UNBIND_H
#define UNBIND_H

#include "smpp/pdu/pdu.h"

namespace smpp {

namespace builder {
class UnbindBuilder;
}

class Unbind final : public Pdu {
 private:
  Unbind();

  friend const std::unordered_map<uint32_t, Pdu::Factory>& getCommandIdToFactoryMap();
  static std::unique_ptr<Unbind> create(std::istream& is);

 public:
  explicit Unbind(const builder::UnbindBuilder& params);

  virtual void serialize(std::ostream& os) const override;

  virtual bool equals(const Pdu& other) const override;
};

}  // namespace smpp

#endif
