#ifndef BIND_RECEIVER_H
#define BIND_RECEIVER_H

#include "basebind.h"

namespace smpp {

class BindReceiver final : public BaseBind {
 public:
  BindReceiver();

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