#ifndef BASEBIND_RESP_H
#define BASEBIND_RESP_H

#include <cereal/types/base_class.hpp>
#include <string>

#include "pdu_response.h"

namespace smpp {

class BaseBindResp : public PduResponse {
 private:
  std::string m_strSystemId;

 protected:
  explicit BaseBindResp(uint32_t nCommandId);

 public:
  std::string getSystemId() const;

  void setSystemId(const std::string& strSystemId);

 private:
  /**
   * Serialization/Deserialization
   */

  friend class cereal::access;

  template <typename Archive>
  void save(Archive& archive) const;

  template <class Archive>
  void load(Archive& archive);
};

template <typename Archive>
void BaseBindResp::save(Archive& archive) const {
  archive(cereal::base_class<Pdu>(this));
  auto serializeNullTerminatedStringCharByChar = [&archive](const std::string& str) {
    for (char c : str) {
      archive(c);
    }
    archive('\0');
  };
  serializeNullTerminatedStringCharByChar(m_strSystemId);
}

template <typename Archive>
void BaseBindResp::load(Archive& archive) {
  archive(cereal::base_class<Pdu>(this));

  auto deserializeNullTerminatedStringCharByChar = [&archive](std::string& str) {
    str = "";
    char c = 'A';
    while (true) {  // TODO SG: Probably not the best thing to do while (true) ...
      archive(c);
      if (c == '\0') {  // std::string adds by default '\0' at the end
        break;
      }
      str += c;
    }
  };

  deserializeNullTerminatedStringCharByChar(m_strSystemId);
}

}  // namespace smpp

#endif