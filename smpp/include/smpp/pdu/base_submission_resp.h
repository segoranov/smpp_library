#ifndef BASE_SUBMISSION_RESP_H
#define BASE_SUBMISSION_RESP_H

#include <string>

#include "smpp/pdu/pdu.h"

namespace smpp {

class BaseSubmissionResp : public Pdu {
 protected:
  std::string m_strMessageId;

 public:
  explicit BaseSubmissionResp(uint32_t nCommandId);

  std::string getMessageId() const;
};

}  // namespace smpp

#endif