#ifndef ENQUIRE_LINK_H
#define ENQUIRE_LINK_H

#include "smpp/pdu/pdu.h"

namespace smpp {

namespace builder {
class EnquireLinkBuilder;
}

class EnquireLink final : public Pdu {
 private:
  EnquireLink();

  friend const std::unordered_map<uint32_t, Pdu::Factory>& getCommandIdToFactoryMap();
  static std::unique_ptr<EnquireLink> create(std::istream& is);

 public:
  explicit EnquireLink(const builder::EnquireLinkBuilder& params);

  virtual void serialize(std::ostream& os) const override;

  virtual bool equals(const Pdu& other) const override;
};

}  // namespace smpp

#endif
