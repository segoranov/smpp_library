#ifndef ALIASES_H
#define ALIASES_H

#include <memory>

#include "transcoder/pdu_transcoder.h"
#include "pdu/pdu.h"

namespace smpp {

using PduTranscoderUPtr = std::unique_ptr<PduTranscoder>;
using PduTranscoderSPtr = std::shared_ptr<PduTranscoder>;



}  // namespace smpp

#endif