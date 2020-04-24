#include "smpp/pdu/enquire_link_resp.h"

#include "smpp/pdu/builder/enquire_link_resp_builder.h"
#include "smpp/util/serialization_util.h"

namespace smpp {

EnquireLinkResp::EnquireLinkResp() : Pdu{constants::CMD_ID_ENQUIRE_LINK_RESP} {}

EnquireLinkResp::EnquireLinkResp(const builder::EnquireLinkRespBuilder& params)
    : Pdu{constants::CMD_ID_ENQUIRE_LINK_RESP} {
  m_nCommandStatus = smpp::constants::command_status::ESME_ROK;
  params.checkAllValuesArePresent();
  m_nSequenceNumber = params.m_optSequenceNumber.value();
  m_nCommandLength = smpp::constants::PDU_HEADER_LENGTH;
}

void EnquireLinkResp::serialize(std::ostream& os) const { Pdu::serialize(os); }

std::unique_ptr<EnquireLinkResp> EnquireLinkResp::create(std::istream& is) {
  // std::cout << "EnquireLinkResp::create()";
  return std::unique_ptr<EnquireLinkResp>{new EnquireLinkResp{}};
}

bool EnquireLinkResp::equals(const Pdu& other) const { return Pdu::equals(other); }

}  // namespace smpp
