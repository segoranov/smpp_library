#ifndef BIND_TRANSCEIVER_H
#define BIND_TRANSCEIVER_H

#include "basebind.h"

namespace smpp {

class BindTransceiver final : public BaseBind {
 public:
  BindTransceiver();

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