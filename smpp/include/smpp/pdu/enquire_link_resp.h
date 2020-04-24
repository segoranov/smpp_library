#ifndef ENQUIRE_LINK_RESP_H
#define ENQUIRE_LINK_RESP_H

#include "smpp/pdu/pdu.h"

namespace smpp {

namespace builder {
class EnquireLinkRespBuilder;
}

class EnquireLinkResp final : public Pdu {
 private:
  EnquireLinkResp();

  friend const std::unordered_map<uint32_t, Pdu::Factory>& getCommandIdToFactoryMap();
  static std::unique_ptr<EnquireLinkResp> create(std::istream& is);

 public:
  explicit EnquireLinkResp(const builder::EnquireLinkRespBuilder& params);

  virtual void serialize(std::ostream& os) const override;

  virtual bool equals(const Pdu& other) const override;
};

}  // namespace smpp

#endif
