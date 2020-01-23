#ifndef SUBMIT_SM_RESP_H
#define SUBMIT_SM_RESP_H

#include "smpp/pdu/base_submission_resp.h"

namespace smpp {

namespace builder {
class SubmitSmRespBuilder;
}

class SubmitSmResp final : public BaseSubmissionResp {
 private:
  SubmitSmResp();

 private:
  friend const std::unordered_map<uint32_t, Pdu::Factory>& getCommandIdToFactoryMap();
  static std::unique_ptr<SubmitSmResp> create(std::istream& is);

 public:
  explicit SubmitSmResp(const builder::SubmitSmRespBuilder& params);

  virtual void serialize(std::ostream& os) const override;
};

}  // namespace smpp

#endif