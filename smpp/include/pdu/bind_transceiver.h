#ifndef BIND_TRANSCEIVER_H
#define BIND_TRANSCEIVER_H

#include "base_bind.h"

namespace smpp {

class BindTransceiver final : public BaseBind {
 private:
  BindTransceiver();

  friend const std::unordered_map<uint32_t, Pdu::BodyFactory>& getCommandIdToBodyFactoryMap();
  static std::unique_ptr<BindTransceiver> createPduBody(std::istream& is);

 public:
  static std::unique_ptr<BindTransceiver> createEmpty();

  virtual void serialize(std::ostream& os) const override;
};

}  // namespace smpp

#endif