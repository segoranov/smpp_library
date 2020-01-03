#ifndef BIND_RECEIVER_H
#define BIND_RECEIVER_H

#include "base_bind.h"

namespace smpp {

class BindReceiver final : public BaseBind {
 private:
  BindReceiver();

  friend const std::unordered_map<uint32_t, Pdu::BodyFactory>& getCommandIdToBodyFactoryMap();
  static std::unique_ptr<BindReceiver> createPduBody(std::istream& is);

 public:
  static std::unique_ptr<BindReceiver> createEmpty();

  virtual void serialize(std::ostream& os) const override;
};

}  // namespace smpp

#endif