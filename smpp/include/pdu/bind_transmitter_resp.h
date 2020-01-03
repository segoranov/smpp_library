#ifndef BIND_TRANSMITTER_RESP_H
#define BIND_TRANSMITTER_RESP_H

#include "base_bind_resp.h"

namespace smpp {

class BindTransmitterResp final : public BaseBindResp {
 private:
  BindTransmitterResp();

  friend const std::unordered_map<uint32_t, Pdu::BodyFactory>& getCommandIdToBodyFactoryMap();
  static std::unique_ptr<BindTransmitterResp> createPduBody(std::istream& is);

 public:
  static std::unique_ptr<BindTransmitterResp> createEmpty();

  virtual void serialize(std::ostream& os) const override;
};

}  // namespace smpp

#endif