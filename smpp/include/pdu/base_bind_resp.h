#ifndef BASE_BIND_RESP_H
#define BASE_BIND_RESP_H

#include <cereal/types/base_class.hpp>
#include <string>

#include "pdu_response.h"

namespace smpp {

class BaseBindResp : public PduResponse {
 protected:
  std::string m_strSystemId;

 protected:
  virtual void serializeBody(std::ostream& os) const final override;
  virtual void deserializeBody(std::istream& is) final override;

 public:
  explicit BaseBindResp(uint32_t nCommandId);

  std::string getSystemId() const;
};

}  // namespace smpp

#endif