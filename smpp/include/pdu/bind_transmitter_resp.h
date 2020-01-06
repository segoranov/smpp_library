#ifndef BIND_TRANSMITTER_RESP_H
#define BIND_TRANSMITTER_RESP_H

#include "base_bind_resp.h"

namespace smpp {

namespace builder {
class BindTransmitterRespBuilder;
}

class BindTransmitterResp final : public BaseBindResp {
 private:
  BindTransmitterResp();

  friend const std::unordered_map<uint32_t, Pdu::BodyFactory>& getCommandIdToBodyFactoryMap();
  static std::unique_ptr<BindTransmitterResp> createPduBody(std::istream& is);

 public:
  explicit BindTransmitterResp(const builder::BindTransmitterRespBuilder& params);

  virtual void serialize(std::ostream& os) const override;
};

}  // namespace smpp

#endif