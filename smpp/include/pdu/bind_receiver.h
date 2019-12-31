#ifndef BIND_RECEIVER_H
#define BIND_RECEIVER_H

#include "base_bind.h"

namespace smpp {

class BindReceiver final : public BaseBind {
 public:
  BindReceiver();

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