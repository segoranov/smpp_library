#ifndef BASE_SUBMISSION_RESP_H
#define BASE_SUBMISSION_RESP_H

#include <string>

#include "smpp/pdu/pdu_response.h"

namespace smpp {

class BaseSubmissionResp : public PduResponse {
 protected:
  std::string m_strMessageId;

 protected:
  virtual void serializeBody(std::ostream& os) const override;
  virtual void deserializeBody(std::istream& is) override;

 public:
  explicit BaseSubmissionResp(uint32_t nCommandId);

  std::string getMessageId() const;
};

}  // namespace smpp

#endif