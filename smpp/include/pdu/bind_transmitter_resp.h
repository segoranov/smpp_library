#ifndef BIND_TRANSMITTER_RESP_H
#define BIND_TRANSMITTER_RESP_H

#include "base_bind_resp.h"

namespace smpp {

class BindTransmitterResp final : public BaseBindResp {
 private:
  BindTransmitterResp();

 public:
  static std::unique_ptr<BindTransmitterResp> createEmpty();
  static std::unique_ptr<Pdu> create(std::istream& is);
  virtual void serialize(std::ostream& os) const override;
};

}  // namespace smpp

#endif