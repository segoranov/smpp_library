#ifndef OUTBIND_H
#define OUTBIND_H

#include "smpp/pdu/pdu.h"

namespace smpp {

namespace builder {
class OutbindBuilder;
}

class Outbind final : public Pdu {
 private:
  Outbind();

  std::string m_strSystemId;
  std::string m_strPassword;

 private:
  friend const std::unordered_map<uint32_t, Pdu::BodyFactory>& getCommandIdToBodyFactoryMap();
  static std::unique_ptr<Outbind> createPduBody(std::istream& is);

  virtual void serializeBody(std::ostream& os) const override;
  virtual void deserializeBody(std::istream& is) override;

 public:
  explicit Outbind(const builder::OutbindBuilder& params);

  virtual void serialize(std::ostream& os) const override;

  std::string getSystemId() const;
  std::string getPassword() const;
};

}  // namespace smpp

#endif