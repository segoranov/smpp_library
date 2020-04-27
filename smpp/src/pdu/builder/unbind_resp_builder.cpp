#include "smpp/pdu/builder/unbind_resp_builder.h"

namespace smpp::builder {

UnbindRespBuilder& UnbindRespBuilder::withCommandStatus(uint32_t nCommandStatus) {
  m_optCommandStatus = nCommandStatus;
  return *this;
}

UnbindRespBuilder& UnbindRespBuilder::withSequenceNumber(uint32_t nSequenceNumber) {
  m_optSequenceNumber = nSequenceNumber;
  return *this;
}

void UnbindRespBuilder::checkAllValuesArePresent() const {
  if (!m_optCommandStatus.has_value())
    throw UndefinedValueException("UnbindRespBuilder: Undefined command status");

  if (!m_optSequenceNumber.has_value()) {
    throw UndefinedValueException("UnbindRespBuilder: Undefined sequence number");
  }
}

}  // namespace smpp::builder