#ifndef BIND_TRANSCEIVER_H
#define BIND_TRANSCEIVER_H

#include "base_bind.h"

namespace smpp {

class BindTransceiver final : public BaseBind {
 private:
  BindTransceiver();

 public:
  virtual void serialize(std::ostream& os) const override;

  static std::unique_ptr<Pdu> createEmpty();
  static std::unique_ptr<Pdu> create(uint32_t nCommandLength, std::istream& is);
};

}  // namespace smpp

#endif