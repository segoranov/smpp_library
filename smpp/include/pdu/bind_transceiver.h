#ifndef BIND_TRANSCEIVER_H
#define BIND_TRANSCEIVER_H

#include "base_bind.h"

namespace smpp {

class BindTransceiver final : public BaseBind {
 public:
  BindTransceiver();

 private:
  /**
   * Serialization/Deserialization
   */

  friend class cereal::access;

  template <typename Archive>
  void save(Archive& archive) const {
    archive(cereal::base_class<BaseBind>(this));
  }

  template <typename Archive>
  void load(Archive& archive) {
    archive(cereal::base_class<BaseBind>(this));
  }
};

}  // namespace smpp

#endif