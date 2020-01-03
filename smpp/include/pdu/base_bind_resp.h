#ifndef BASE_BIND_RESP_H
#define BASE_BIND_RESP_H

#include <cereal/types/base_class.hpp>
#include <string>

#include "pdu_response.h"

namespace smpp {

class BaseBindResp : public PduResponse {
 private:
  std::string m_strSystemId;

 protected:
  virtual void serializeBody(std::ostream& os) const final;
  virtual void deserializeBody(std::istream& is) final;

 public:
  explicit BaseBindResp(uint32_t nCommandId);

  std::string getSystemId() const;

  void setSystemId(const std::string& strSystemId);
};

}  // namespace smpp

#endif