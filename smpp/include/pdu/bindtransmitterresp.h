#ifndef BIND_TRANSMITTER_RESP_H
#define BIND_TRANSMITTER_RESP_H

#include "basebindresp.h"

namespace smpp {

class BindTransmitterResp final : public BaseBindResp {
 public:
  BindTransmitterResp();

 private:
  /**
   * Serialization/Deserialization
   */

  friend class cereal::access;

  template <typename Archive>
  void save(Archive& archive) const {
    archive(cereal::base_class<BaseBindResp>(this));
  }

  template <typename Archive>
  void load(Archive& archive) {
    archive(cereal::base_class<BaseBindResp>(this));
  }
};

}  // namespace smpp

#endif