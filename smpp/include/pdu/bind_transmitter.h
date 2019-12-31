#ifndef BIND_TRANSMITTER_H
#define BIND_TRANSMITTER_H

#include "base_bind.h"

namespace smpp {

class BindTransmitter final : public BaseBind {
 public:
  BindTransmitter();

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