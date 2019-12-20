#ifndef BIND_TRANSMITTER_H
#define BIND_TRANSMITTER_H

#include "basebind.h"

namespace smpp {

class BindTransmitter final : public BaseBind {
 public:
  BindTransmitter();
};

}  // namespace smpp

#endif