#ifndef UNBIND_RESP_H
#define UNBIND_RESP_H

#include "smpp/pdu/pdu.h"

namespace smpp {

namespace builder {
class UnbindRespBuilder;
}

class UnbindResp final : public Pdu {
 private:
  UnbindResp();

  friend const std::unordered_map<uint32_t, Pdu::Factory>& getCommandIdToFactoryMap();
  static std::unique_ptr<UnbindResp> create(std::istream& is);

 public:
  explicit UnbindResp(const builder::UnbindRespBuilder& params);

  virtual void serialize(std::ostream& os) const override;

  virtual bool equals(const Pdu& other) const override;
};

}  // namespace smpp

#endif
