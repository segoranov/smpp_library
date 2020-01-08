#include "smpp/pdu/base_submit.h"

#include "smpp/pdu/pdu_request.h"
#include "smpp/util/serialization_util.h"

namespace smpp {

BaseSubmit::BaseSubmit(uint32_t nCommandId) : PduRequest{nCommandId} {}

std::string BaseSubmit::getServiceType() const { return m_strServiceType; }

uint8_t BaseSubmit::getSourceAddrTon() const { return m_nSourceAddrTon; }

uint8_t BaseSubmit::getSourceAddrNpi() const { return m_nSourceAddrNpi; }

std::string BaseSubmit::getSourceAddr() const { return m_strSourceAddr; }

uint8_t BaseSubmit::getEsmClass() const { return m_nEsmClass; }

uint8_t BaseSubmit::getProtocolId() const { return m_nProtocolId; }

std::string BaseSubmit::getScheduleDeliveryTime() const { return m_strScheduleDeliveryTime; }

std::string BaseSubmit::getValidityPeriod() const { return m_strValidityPeriod; }

uint8_t BaseSubmit::getRegisteredDelivery() const { return m_nRegisteredDelivery; }

uint8_t BaseSubmit::getReplaceIfPresentFlag() const { return m_nReplaceIfPresentFlag; }

uint8_t BaseSubmit::getDataCoding() const { return m_nDataCoding; }

uint8_t BaseSubmit::getSmDefaultMsgId() const { return m_nSmDefaultMsgId; }

uint8_t BaseSubmit::getSmLength() const { return m_nSmLength; }

std::string BaseSubmit::getShortMessage() const { return m_strShortMessage; }

}  // namespace smpp