#ifndef BIND_RECEIVER_H
#define BIND_RECEIVER_H

#include "base_bind.h"

namespace smpp {

class BindReceiver final : public BaseBind {
 private:
  BindReceiver();

 public:
  virtual void serialize(std::ostream& os) const override;

  static std::unique_ptr<Pdu> createEmpty();
  static std::unique_ptr<Pdu> create(uint32_t nCommandLength, std::istream& is);
};

}  // namespace smpp

#endif