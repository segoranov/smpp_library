#ifndef BIND_TRANSMITTER_RESP_H
#define BIND_TRANSMITTER_RESP_H

#include "base_bind_resp.h"

namespace smpp {

class BindTransmitterResp final : public BaseBindResp {
 public:
  BindTransmitterResp();

  virtual void serialize(std::ostream& os) const override;
};

}  // namespace smpp

#endif