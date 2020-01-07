#ifndef SUBMIT_SM_RESP_H
#define SUBMIT_SM_RESP_H

#include "pdu/base_submission_resp.h"

namespace smpp {

namespace builder {
class SubmitSmRespBuilder;
}

class SubmitSmResp final : public BaseSubmissionResp {
 private:
  SubmitSmResp();

 private:
  friend const std::unordered_map<uint32_t, Pdu::BodyFactory>& getCommandIdToBodyFactoryMap();
  static std::unique_ptr<SubmitSmResp> createPduBody(std::istream& is);

  virtual void serializeBody(std::ostream& os) const override;
  virtual void deserializeBody(std::istream& is) override;

 public:
  explicit SubmitSmResp(const builder::SubmitSmRespBuilder& params);

  virtual void serialize(std::ostream& os) const override;
};
}  // namespace smpp

#endif