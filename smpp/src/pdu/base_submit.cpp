#include "smpp/pdu/base_submit.h"

#include "smpp/pdu/pdu.h"
#include "smpp/util/serialization_util.h"

namespace smpp {

BaseSubmit::BaseSubmit(uint32_t nCommandId) : Pdu{nCommandId} {}

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

bool BaseSubmit::equals(const Pdu& other) const {
  if (!Pdu::equals(other)) {
    return false;
  }

  auto otherBase = static_cast<const BaseSubmit*>(&other);

  return m_strServiceType == otherBase->m_strServiceType &&
         m_nSourceAddrTon == otherBase->m_nSourceAddrTon &&
         m_nSourceAddrNpi == otherBase->m_nSourceAddrNpi &&
         m_strSourceAddr == otherBase->m_strSourceAddr && m_nEsmClass == otherBase->m_nEsmClass &&
         m_nProtocolId == otherBase->m_nProtocolId &&
         m_nPriorityFlag == otherBase->m_nPriorityFlag &&
         m_strScheduleDeliveryTime == otherBase->m_strScheduleDeliveryTime &&
         m_strValidityPeriod == otherBase->m_strValidityPeriod &&
         m_nReplaceIfPresentFlag == otherBase->m_nReplaceIfPresentFlag &&
         m_nDataCoding == otherBase->m_nDataCoding &&
         m_nSmDefaultMsgId == otherBase->m_nSmDefaultMsgId &&
         m_nSmLength == otherBase->m_nSmLength &&
         m_strShortMessage == otherBase->m_strShortMessage;
}

}  // namespace smpp