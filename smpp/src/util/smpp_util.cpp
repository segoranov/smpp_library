#include "smpp/util/smpp_util.h"

#include <algorithm>

#include "smpp/smpp_constants.h"
#include "smpp/smpp_exceptions.h"
namespace smpp::util {

bool isCommandLengthValid(uint32_t nCommandLength) {
  return constants::PDU_HEADER_LENGTH <= nCommandLength &&
         nCommandLength <= constants::PDU_MAX_LENGTH;
}

bool isTlvTagValid(uint16_t nTag) {
  auto it = std::find(constants::ALL_TLV_TAGS.begin(), constants::ALL_TLV_TAGS.end(), nTag);
  return it != constants::ALL_TLV_TAGS.end();
}

bool isCommandIdValid(uint32_t nCommandId) {
  auto it =
      std::find(constants::ALL_COMMAND_IDS.begin(), constants::ALL_COMMAND_IDS.end(), nCommandId);
  return it != constants::ALL_COMMAND_IDS.end();
}

bool isInterfaceVersionValid(uint8_t nInterfaceVersion) {
  return nInterfaceVersion == constants::VERSION_3_3 ||
         nInterfaceVersion == constants::VERSION_3_4 ||
         nInterfaceVersion == constants::VERSION_5_0;
}

std::string commandIdToString(uint32_t nCommandId) {
  switch (nCommandId) {
    case constants::CMD_ID_BIND_RECEIVER:
      return "BIND_RECEIVER";
    case constants::CMD_ID_BIND_TRANSMITTER:
      return "BIND_TRANSMITTER";
    case constants::CMD_ID_QUERY_SM:
      return "QUERY_SM";
    case constants::CMD_ID_SUBMIT_SM:
      return "SUBMIT_SM";
    case constants::CMD_ID_DELIVER_SM:
      return "DELIVER_SM";
    case constants::CMD_ID_UNBIND:
      return "UNBID";
    case constants::CMD_ID_REPLACE_SM:
      return "REPLACE_SM";
    case constants::CMD_ID_CANCEL_SM:
      return "CANCEL_SM";
    case constants::CMD_ID_BIND_TRANSCEIVER:
      return "BIND_TRANSMITTER";
    case constants::CMD_ID_OUTBIND:
      return "OUTBIND";
    case constants::CMD_ID_ENQUIRE_LINK:
      return "ENQUIRE_LINK";
    case constants::CMD_ID_SUBMIT_MULTI:
      return "SUBMIT_MULTI";
    case constants::CMD_ID_ALERT_NOTIFICATION:
      return "ALERT_NOTIFICATION";
    case constants::CMD_ID_DATA_SM:
      return "DATA_SM";
    case constants::CMD_ID_BROADCAST_SM:
      return "BROADCAST_SM";
    case constants::CMD_ID_QUERY_BROADCAST_SM:
      return "QUERY_BROADCAST_SM";
    case constants::CMD_ID_CANCEL_BROADCAST_SM:
      return "CANCEL_BROADCAST_SM";
    case constants::CMD_ID_GENERIC_NACK:
      return "GENERIC_NACK";
    case constants::CMD_ID_BIND_RECEIVER_RESP:
      return "BIND_RECEIVER_RESP";
    case constants::CMD_ID_BIND_TRANSMITTER_RESP:
      return "BIND_TRANSMITTER_RESP";
    case constants::CMD_ID_QUERY_SM_RESP:
      return "QUERY_SM_RESP";
    case constants::CMD_ID_SUBMIT_SM_RESP:
      return "SUBMIT_SM_RESP";
    case constants::CMD_ID_DELIVER_SM_RESP:
      return "DELIVER_SM_RESP";
    case constants::CMD_ID_UNBIND_RESP:
      return "UNBIND_RESP";
    case constants::CMD_ID_REPLACE_SM_RESP:
      return "REPLACE_SM_RESP";
    case constants::CMD_ID_CANCEL_SM_RESP:
      return "CANCEL_SM_RESP";
    case constants::CMD_ID_BIND_TRANSCEIVER_RESP:
      return "BIND_TRANSCEIVER_RESP";
    case constants::CMD_ID_ENQUIRE_LINK_RESP:
      return "ENQUIRE_LINK_RESP";
    case constants::CMD_ID_SUBMIT_MULTI_RESP:
      return "SUBMIT_MULTI_RESP";
    case constants::CMD_ID_DATA_SM_RESP:
      return "DATA_SM_RESP";
    case constants::CMD_ID_BROADCAST_SM_RESP:
      return "BROADCAST_SM_RESP";
    case constants::CMD_ID_QUERY_BROADCAST_SM_RESP:
      return "QUERY_BROADCAST_SM_RESP";
    case constants::CMD_ID_CANCEL_BROADCAST_SM_RESP:
      return "CANCEL_BROADCAST_SM_RESP";
    default:
      return "UNKNOWN_COMMAND_ID";
  }
}

}  // namespace smpp::util
