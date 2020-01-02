#ifndef BIND_TRANSMITTER_H
#define BIND_TRANSMITTER_H

#include "base_bind.h"

namespace smpp {

class BindTransmitter final : public BaseBind {
 private:
  BindTransmitter();

 public:
  virtual void serialize(std::ostream& os) const override;

  static std::unique_ptr<BindTransmitter> createEmpty();
  static std::unique_ptr<Pdu> create(std::istream& is);
};

}  // namespace smpp

#endif