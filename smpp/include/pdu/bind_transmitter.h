#ifndef BIND_TRANSMITTER_H
#define BIND_TRANSMITTER_H

#include "base_bind.h"

namespace smpp {

namespace builder {
class BindTransmitterBuilder;
}
class BindTransmitter final : public BaseBind {
 private:
  BindTransmitter();

  friend const std::unordered_map<uint32_t, Pdu::BodyFactory>& getCommandIdToBodyFactoryMap();
  static std::unique_ptr<BindTransmitter> createPduBody(std::istream& is);

 public:
  explicit BindTransmitter(const builder::BindTransmitterBuilder& params);

  virtual void serialize(std::ostream& os) const override;
};

}  // namespace smpp

#endif