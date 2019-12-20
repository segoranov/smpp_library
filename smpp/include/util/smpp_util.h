#ifndef SMPP_UTIL_H
#define SMPP_UTIL_H

#include <memory>

#include "pdu/bindtransmitter.h"
#include "smppconstants.h"

namespace smpp::util {

std::unique_ptr<Pdu> createPduByCommandId(uint32_t nCommandId);

}

#endif