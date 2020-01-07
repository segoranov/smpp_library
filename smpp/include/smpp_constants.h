#ifndef SMPP_CONSTANTS_H
#define SMPP_CONSTANTS_H

#include <string>
#include <unordered_map>
#include <vector>

namespace smpp::constants {
/**
 * SMPP Data Types
 */
constexpr int DATA_TYPE_C_OCTET_STRING = 0;
constexpr int DATA_TYPE_OCTET_STRING = 1;
constexpr int DATA_TYPE_INTEGER = 2;

constexpr int PDU_HEADER_FIELD_LENGTH = 4;
constexpr int PDU_HEADER_LENGTH = 16;
constexpr int PDU_MAX_LENGTH = 140;               // max octets for a PDU
constexpr int PDU_CMD_ID_RESP_MASK = 0x80000000;  // 31st bit set to true
// constexpr Address EMPTY_ADDRESS = new Address();

constexpr uint8_t VERSION_3_3 = 0x33;
constexpr uint8_t VERSION_3_4 = 0x34;
constexpr uint8_t VERSION_5_0 = 0x50;

constexpr int DEFAULT_WINDOW_SIZE = 1;
constexpr long DEFAULT_WINDOW_WAIT_TIMEOUT = 60000;
constexpr long DEFAULT_WRITE_TIMEOUT = 0;  // For backwards compatibility, default to no timeout
constexpr long DEFAULT_CONNECT_TIMEOUT = 10000;
constexpr long DEFAULT_BIND_TIMEOUT = 5000;
constexpr long DEFAULT_REQUEST_EXPIRY_TIMEOUT = -1;   // disabled
constexpr long DEFAULT_WINDOW_MONITOR_INTERVAL = -1;  // disabled
constexpr int DEFAULT_SERVER_MAX_CONNECTION_SIZE = 100;
constexpr bool DEFAULT_SERVER_NON_BLOCKING_SOCKETS_ENABLED = true;
constexpr bool DEFAULT_SERVER_REUSE_ADDRESS = true;

namespace null_settings {
constexpr uint8_t NULL_INT8 = 0x00;
constexpr uint16_t NULL_INT16 = 0x0000;
constexpr uint32_t NULL_INT32 = 0x00000000;
const std::string NULL_C_OCTET_STRING = "";

}  // namespace null_settings

//
// SUBMIT_MULTI destination type flags
//
// constexpr int SME_ADDRESS = 1;
// constexpr int DISTRIBUTION_LIST_NAME = 2;

/**
 * SMPP Command ID (Requests)
 */
constexpr uint32_t CMD_ID_BIND_RECEIVER = 0x00000001;
constexpr uint32_t CMD_ID_BIND_TRANSMITTER = 0x00000002;
constexpr uint32_t CMD_ID_QUERY_SM = 0x00000003;
constexpr uint32_t CMD_ID_SUBMIT_SM = 0x00000004;
constexpr uint32_t CMD_ID_DELIVER_SM = 0x00000005;
constexpr uint32_t CMD_ID_UNBIND = 0x00000006;
constexpr uint32_t CMD_ID_REPLACE_SM = 0x00000007;
constexpr uint32_t CMD_ID_CANCEL_SM = 0x00000008;
constexpr uint32_t CMD_ID_BIND_TRANSCEIVER = 0x00000009;
constexpr uint32_t CMD_ID_OUTBIND = 0x0000000B;
constexpr uint32_t CMD_ID_ENQUIRE_LINK = 0x00000015;
constexpr uint32_t CMD_ID_SUBMIT_MULTI = 0x00000021;
constexpr uint32_t CMD_ID_ALERT_NOTIFICATION = 0x00000102;
constexpr uint32_t CMD_ID_DATA_SM = 0x00000103;
constexpr uint32_t CMD_ID_BROADCAST_SM = 0x00000111;
constexpr uint32_t CMD_ID_QUERY_BROADCAST_SM = 0x00000112;
constexpr uint32_t CMD_ID_CANCEL_BROADCAST_SM = 0x00000113;

/**
 * SMPP Command ID (Responses)
 */
constexpr uint32_t CMD_ID_GENERIC_NACK = 0x80000000;
constexpr uint32_t CMD_ID_BIND_RECEIVER_RESP = 0x80000001;
constexpr uint32_t CMD_ID_BIND_TRANSMITTER_RESP = 0x80000002;
constexpr uint32_t CMD_ID_QUERY_SM_RESP = 0x80000003;
constexpr uint32_t CMD_ID_SUBMIT_SM_RESP = 0x80000004;
constexpr uint32_t CMD_ID_DELIVER_SM_RESP = 0x80000005;
constexpr uint32_t CMD_ID_UNBIND_RESP = 0x80000006;
constexpr uint32_t CMD_ID_REPLACE_SM_RESP = 0x80000007;
constexpr uint32_t CMD_ID_CANCEL_SM_RESP = 0x80000008;
constexpr uint32_t CMD_ID_BIND_TRANSCEIVER_RESP = 0x80000009;
constexpr uint32_t CMD_ID_ENQUIRE_LINK_RESP = 0x80000015;
constexpr uint32_t CMD_ID_SUBMIT_MULTI_RESP = 0x80000021;
constexpr uint32_t CMD_ID_DATA_SM_RESP = 0x80000103;
constexpr uint32_t CMD_ID_BROADCAST_SM_RESP = 0x80000111;
constexpr uint32_t CMD_ID_QUERY_BROADCAST_SM_RESP = 0x80000112;
constexpr uint32_t CMD_ID_CANCEL_BROADCAST_SM_RESP = 0x80000113;

// vector containing all command ids; just for convenience if needed
const std::vector<uint32_t> ALL_COMMAND_IDS{
    0x00000001, 0x00000002, 0x00000003, 0x00000004, 0x00000005, 0x00000006, 0x00000007,
    0x00000008, 0x00000009, 0x0000000B, 0x00000015, 0x00000021, 0x00000102, 0x00000103,
    0x00000111, 0x00000112, 0x00000113, 0x80000000, 0x80000001, 0x80000002, 0x80000003,
    0x80000004, 0x80000005, 0x80000006, 0x80000007, 0x80000008, 0x80000009, 0x80000015,
    0x80000021, 0x80000103, 0x80000111, 0x80000112, 0x80000113};

/**
 * Optional TLV tags
 */
constexpr uint16_t TAG_DEST_ADDR_SUBUNIT = 0x0005;
constexpr uint16_t TAG_DEST_NETWORK_TYPE = 0x0006;
constexpr uint16_t TAG_DEST_BEARER_TYPE = 0x0007;
constexpr uint16_t TAG_DEST_TELEMATICS_ID = 0x0008;
constexpr uint16_t TAG_SOURCE_ADDR_SUBUNIT = 0x000D;
constexpr uint16_t TAG_SOURCE_NETWORK_TYPE = 0x000E;
constexpr uint16_t TAG_SOURCE_BEARER_TYPE = 0x000F;
constexpr uint16_t TAG_SOURCE_TELEMATICS_ID = 0x0010;
constexpr uint16_t TAG_QOS_TIME_TO_LIVE = 0x0017;
constexpr uint16_t TAG_PAYLOAD_TYPE = 0x0019;
constexpr uint16_t TAG_ADDITIONAL_ESME_RINFO_TEXT = 0x001D;
constexpr uint16_t TAG_RECEIPTED_MESSAGE_ID = 0x001E;
constexpr uint16_t TAG_MS_MSG_WAIT_FACILITIES = 0x0030;
constexpr uint16_t TAG_PRIVACY_INDICATOR = 0x0201;
constexpr uint16_t TAG_SOURCE_SUBADDRESS = 0x0202;
constexpr uint16_t TAG_DEST_SUBADDRESS = 0x0203;
constexpr uint16_t TAG_USER_MESSAGE_REFERENCE = 0x0204;
constexpr uint16_t TAG_USER_RESPONSE_CODE = 0x0205;
constexpr uint16_t TAG_SOURCE_PORT = 0x020A;
constexpr uint16_t TAG_DEST_PORT = 0x020B;
constexpr uint16_t TAG_SAR_MSG_REF_NUM = 0x020C;
constexpr uint16_t TAG_LANGUAGE_INDICATOR = 0x020D;
constexpr uint16_t TAG_SAR_TOTAL_SEGMENTS = 0x020E;
constexpr uint16_t TAG_SAR_SEGMENT_SEQNUM = 0x020F;
constexpr uint16_t TAG_SC_INTERFACE_VERSION = 0x0210;
constexpr uint16_t TAG_CALLBACK_NUM_PRES_IND = 0x0302;
constexpr uint16_t TAG_CALLBACK_NUM_ATAG = 0x0303;
constexpr uint16_t TAG_NUMBER_OF_MESSAGES = 0x0304;
constexpr uint16_t TAG_CALLBACK_NUM = 0x0381;
constexpr uint16_t TAG_DPF_RESULT = 0x0420;
constexpr uint16_t TAG_SET_DPF = 0x0421;
constexpr uint16_t TAG_MS_AVAILABILITY_STATUS = 0x0422;
constexpr uint16_t TAG_NETWORK_ERROR_CODE = 0x0423;
constexpr uint16_t TAG_MESSAGE_PAYLOAD = 0x0424;
constexpr uint16_t TAG_DELIVERY_FAILURE_REASON = 0x0425;
constexpr uint16_t TAG_MORE_MESSAGES_TO_SEND = 0x0426;
constexpr uint16_t TAG_MESSAGE_STATE = 0x0427;
constexpr uint16_t TAG_CONGESTION_STATE = 0x0428;
constexpr uint16_t TAG_USSD_SERVICE_OP = 0x0501;
constexpr uint16_t TAG_BROADCAST_CHANNEL_INDICATOR = 0x0600;
constexpr uint16_t TAG_BROADCAST_CONTENT_TYPE = 0x0601;
constexpr uint16_t TAG_BROADCAST_CONTENT_TYPE_INFO = 0x0602;
constexpr uint16_t TAG_BROADCAST_MESSAGE_CLASS = 0x0603;
constexpr uint16_t TAG_BROADCAST_REP_NUM = 0x0604;
constexpr uint16_t TAG_BROADCAST_FREQUENCY_INTERVAL = 0x0605;
constexpr uint16_t TAG_BROADCAST_AREA_IDENTIFIER = 0x0606;
constexpr uint16_t TAG_BROADCAST_ERROR_STATUS = 0x0607;
constexpr uint16_t TAG_BROADCAST_AREA_SUCCESS = 0x0608;
constexpr uint16_t TAG_BROADCAST_END_TIME = 0x0609;
constexpr uint16_t TAG_BROADCAST_SERVICE_GROUP = 0x060A;
constexpr uint16_t TAG_BILLING_IDENTIFICATION = 0x060B;
constexpr uint16_t TAG_SOURCE_NETWORK_ID = 0x060D;
constexpr uint16_t TAG_DEST_NETWORK_ID = 0x060E;
constexpr uint16_t TAG_SOURCE_NODE_ID = 0x060F;
constexpr uint16_t TAG_DEST_NODE_ID = 0x0610;
constexpr uint16_t TAG_DEST_ADDR_NP_RESOLUTION = 0x0611;
constexpr uint16_t TAG_DEST_ADDR_NP_INFORMATION = 0x0612;
constexpr uint16_t TAG_DEST_ADDR_NP_COUNTRY = 0x0613;
constexpr uint16_t TAG_DISPLAY_TIME = 0x1201;
constexpr uint16_t TAG_SMS_SIGNAL = 0x1203;
constexpr uint16_t TAG_MS_VALIDITY = 0x1204;
constexpr uint16_t TAG_ALERT_ON_MESSAGE_DELIVERY = 0x130C;
constexpr uint16_t TAG_ITS_REPLY_TYPE = 0x1380;
constexpr uint16_t TAG_ITS_SESSION_INFO = 0x1383;

// vector containing all TLV tags; just for convenience if needed
const std::vector<uint16_t> ALL_TLV_TAGS{
    0x0005, 0x0006, 0x0007, 0x0008, 0x000D, 0x000E, 0x000F, 0x0010, 0x0017, 0x0019, 0x001D,
    0x001E, 0x0030, 0x0201, 0x0202, 0x0203, 0x0204, 0x0205, 0x020A, 0x020B, 0x020C, 0x020D,
    0x020E, 0x020F, 0x0210, 0x0302, 0x0303, 0x0304, 0x0381, 0x0420, 0x0421, 0x0422, 0x0423,
    0x0424, 0x0425, 0x0426, 0x0427, 0x0428, 0x0501, 0x0600, 0x0601, 0x0602, 0x0603, 0x0604,
    0x0605, 0x0606, 0x0607, 0x0608, 0x0609, 0x060A, 0x060B, 0x060D, 0x060E, 0x060F, 0x0610,
    0x0611, 0x0612, 0x0613, 0x1201, 0x1203, 0x1204, 0x130C, 0x1380, 0x1383,
};

/** ESM Class */

/** Message Mode (bits 1-0) */
constexpr uint16_t ESM_CLASS_MM_MASK = 0x03;           // BIN 00000011
constexpr uint16_t ESM_CLASS_MM_DEFAULT = 0x00;        // BIN 00000000
constexpr uint16_t ESM_CLASS_MM_DATAGRAM = 0x01;       // BIN 00000001
constexpr uint16_t ESM_CLASS_MM_TRANSACTION = 0x02;    // BIN 00000010
constexpr uint16_t ESM_CLASS_MM_STORE_FORWARD = 0x03;  // BIN 00000011

/** Message Type (bits 5-2) */
// BIN:  11100
constexpr uint16_t ESM_CLASS_MT_MASK = 0x1C;
// BIN: 100, Recv Msg contains SMSC delivery receipt
constexpr uint16_t ESM_CLASS_MT_SMSC_DELIVERY_RECEIPT = 0x04;
// BIN: 1000, Send/Recv Msg contains ESME delivery acknowledgement
constexpr uint16_t ESM_CLASS_MT_ESME_DELIVERY_RECEIPT = 0x08;
// BIN: 10000, Send/Recv Msg contains manual/user acknowledgment
constexpr uint16_t ESM_CLASS_MT_MANUAL_USER_ACK = 0x10;
// BIN: 11000, Recv Msg contains conversation abort (Korean CDMA)
constexpr uint16_t ESM_CLASS_MT_CONVERSATION_ABORT = 0x18;

// I believe this flag is separate from the types above...
// BIN: 100000, Recv Msg contains intermediate notification
constexpr uint16_t ESM_CLASS_INTERMEDIATE_DELIVERY_RECEIPT_FLAG = 0x20;
constexpr uint16_t ESM_CLASS_UDHI_MASK = 0x40;
constexpr uint16_t ESM_CLASS_REPLY_PATH_MASK = 0x80;

/** Registered delivery */

//   SMSC Delivery Receipt (bits 1 & 0)
constexpr uint16_t REGISTERED_DELIVERY_SMSC_RECEIPT_MASK = 0x03;
constexpr uint16_t REGISTERED_DELIVERY_SMSC_RECEIPT_NOT_REQUESTED = 0x00;
constexpr uint16_t REGISTERED_DELIVERY_SMSC_RECEIPT_REQUESTED = 0x01;
constexpr uint16_t REGISTERED_DELIVERY_SMSC_RECEIPT_ON_FAILURE = 0x02;
constexpr uint16_t REGISTERED_DELIVERY_SMSC_RECEIPT_ON_SUCCESS = 0x03;

//   SME originated acknowledgement (bits 3 & 2)
constexpr uint16_t REGISTERED_DELIVERY_SME_ACK_MASK = 0x0c;
constexpr uint16_t REGISTERED_DELIVERY_SME_ACK_NOT_REQUESTED = 0x00;
constexpr uint16_t REGISTERED_DELIVERY_SME_ACK_DELIVERY_REQUESTED = 0x04;
constexpr uint16_t REGISTERED_DELIVERY_SME_ACK_MANUAL_REQUESTED = 0x08;
constexpr uint16_t REGISTERED_DELIVERY_SME_ACK_BOTH_REQUESTED = 0x0c;

// Intermediate notification (bit 4)
// NOTE: SMPP 3.4 specs originally wrote (bit 5) but their matrix actually used
// bit 4 the confirmed value is bit 4, not 5.
constexpr uint16_t REGISTERED_DELIVERY_INTERMEDIATE_NOTIFICATION_MASK = 0x10;
constexpr uint16_t REGISTERED_DELIVERY_INTERMEDIATE_NOTIFICATION_NOT_REQUESTED = 0x00;
constexpr uint16_t REGISTERED_DELIVERY_INTERMEDIATE_NOTIFICATION_REQUESTED = 0x10;

// Replace if Present flag
constexpr int SM_NOREPLACE = 0;
constexpr int SM_REPLACE = 1;

// Destination flag
constexpr int SM_DEST_SME_ADDRESS = 1;
constexpr int SM_DEST_DL_NAME = 2;

// Higher Layer Message Type
constexpr int SM_LAYER_WDP = 0;
constexpr int SM_LAYER_WCMP = 1;

// Operation Class
constexpr int SM_OPCLASS_DATAGRAM = 0;
constexpr int SM_OPCLASS_TRANSACTION = 3;

//
// SMPP Message States
//
constexpr uint16_t STATE_ENROUTE = 0x01;
constexpr uint16_t STATE_DELIVERED = 0x02;
constexpr uint16_t STATE_EXPIRED = 0x03;
constexpr uint16_t STATE_DELETED = 0x04;
constexpr uint16_t STATE_UNDELIVERABLE = 0x05;
constexpr uint16_t STATE_ACCEPTED = 0x06;
constexpr uint16_t STATE_UNKNOWN = 0x07;
constexpr uint16_t STATE_REJECTED = 0x08;

//
// SMPP TON
//
constexpr uint16_t TON_UNKNOWN = 0x00;
constexpr uint16_t TON_INTERNATIONAL = 0x01;
constexpr uint16_t TON_NATIONAL = 0x02;
constexpr uint16_t TON_NETWORK = 0x03;
constexpr uint16_t TON_SUBSCRIBER = 0x04;
constexpr uint16_t TON_ALPHANUMERIC = 0x05;
constexpr uint16_t TON_ABBREVIATED = 0x06;
constexpr uint16_t TON_RESERVED_EXTN = 0x07;

//
// SMPP NPI
//
constexpr uint16_t NPI_UNKNOWN = 0x00;
constexpr uint16_t NPI_E164 = 0x01;
constexpr uint16_t NPI_ISDN = 0x02;
constexpr uint16_t NPI_X121 = 0x03;
constexpr uint16_t NPI_TELEX = 0x04;
constexpr uint16_t NPI_LAND_MOBILE = 0x06;
constexpr uint16_t NPI_NATIONAL = 0x08;
constexpr uint16_t NPI_PRIVATE = 0x09;
constexpr uint16_t NPI_ERMES = 0x0A;
constexpr uint16_t NPI_INTERNET = 0x0E;
constexpr uint16_t NPI_WAP_CLIENT_ID = 0x12;

/**
 * SMPP Data Coding
 */
constexpr uint16_t DATA_CODING_DEFAULT = 0x00;  // SMSC Default Alphabet
constexpr uint16_t DATA_CODING_IA5 = 0x01;      // IA5 (CCITT T.50)/ASCII (ANSI X3.4)

constexpr uint16_t DATA_CODING_8BITA = 0x02;   // Octet unspecified (8-bit binary) defined for TDMA
                                               // and/ or CDMA but not defined for GSM
constexpr uint16_t DATA_CODING_LATIN1 = 0x03;  // Latin 1 (ISO-8859-1)
constexpr uint16_t DATA_CODING_8BIT = 0x04;    // Octet unspecified (8-bit binary) ALL TECHNOLOGIES
constexpr uint16_t DATA_CODING_JIS = 0x05;     // JIS (X 0208-1990)
constexpr uint16_t DATA_CODING_CYRLLIC = 0x06;  // Cyrllic (ISO-8859-5)
constexpr uint16_t DATA_CODING_HEBREW = 0x07;   // Latin/Hebrew (ISO-8859-8)
constexpr uint16_t DATA_CODING_UCS2 = 0x08;     // UCS2 (ISO/IEC-10646)
constexpr uint16_t DATA_CODING_PICTO = 0x09;    // Pictogram Encoding
constexpr uint16_t DATA_CODING_MUSIC = 0x0A;    // ISO-2022-JP (Music Codes)
constexpr uint16_t DATA_CODING_RSRVD = 0x0B;    // reserved
constexpr uint16_t DATA_CODING_RSRVD2 = 0x0C;   // reserved
constexpr uint16_t DATA_CODING_EXKANJI = 0x0D;  // Extended Kanji JIS(X 0212-1990)
constexpr uint16_t DATA_CODING_KSC5601 = 0x0E;  // KS C 5601
constexpr uint16_t DATA_CODING_RSRVD3 = 0x0F;   // reserved

namespace errors {

/**
 * Standard SMPP Error Codes
 */
// 0x00000000: No Error
constexpr int ESME_ROK = 0x00000000;

// Message Length is invalid
constexpr int ESME_RINVMSGLEN = 0x00000001;

// Command Length is invalid
constexpr int ESME_RINVCMDLEN = 0x00000002;

// Invalid Command ID
constexpr int ESME_RINVCMDID = 0x00000003;

// Incorrect BIND Status for given command
constexpr int ESME_RINVBNDSTS = 0x00000004;

// ESME Already in Bound State
constexpr int ESME_RALYBND = 0x00000005;

// Invalid Priority Flag
constexpr int ESME_RINVPRTFLG = 0x00000006;

// Invalid Registered Delivery Flag
constexpr int ESME_RINVREGDLVFLG = 0x00000007;

// System Error
constexpr int ESME_RSYSERR = 0x00000008;

// 0x00000009 Reserved

// Invalid Source Address
constexpr int ESME_RINVSRCADR = 0x0000000A;

// Invalid Dest Addr
constexpr int ESME_RINVDSTADR = 0x0000000B;

// Message ID is invalid
constexpr int ESME_RINVMSGID = 0x0000000C;

// Bind Failed
constexpr int ESME_RBINDFAIL = 0x0000000D;

// Invalid Password
constexpr int ESME_RINVPASWD = 0x0000000E;

// Invalid System ID
constexpr int ESME_RINVSYSID = 0x0000000F;

// 0x00000010 Reserved

// Cancel SM Failed
constexpr int ESME_RCANCELFAIL = 0x00000011;

// 0x00000012 Reserved

// Replace SM Failed
constexpr int ESME_RREPLACEFAIL = 0x00000013;

// Message Queue Full
constexpr int ESME_RMSGQFUL = 0x00000014;

// Invalid Service Type
constexpr int ESME_RINVSERTYP = 0x00000015;

// 0x00000016-0x00000032 Reserved

// Invalid number of destinations
constexpr int ESME_RINVNUMDESTS = 0x00000033;
// Invalid Distribution List name
constexpr int ESME_RINVDLNAME = 0x00000034;

// 0x00000035-0x0000003F Reserved

// Destination flag is invalid (submit_multi)
constexpr int ESME_RINVDESTFLAG = 0x00000040;

// 0x00000041 Reserved

// Invalid ‘submit with replace’ request
// (i.e. submit_sm with replace_if_present_flag set)
constexpr int ESME_RINVSUBREP = 0x00000042;

// Invalid esm_class field data
constexpr int ESME_RINVESMCLASS = 0x00000043;

// Cannot Submit to Distribution List
constexpr int ESME_RCNTSUBDL = 0x00000044;

// submit_sm or submit_multi failed
constexpr int ESME_RSUBMITFAIL = 0x00000045;

// 0x00000046-0x00000047 Reserved

// Invalid Source address TON
constexpr int ESME_RINVSRCTON = 0x00000048;

// Invalid Source address NPI
constexpr int ESME_RINVSRCNPI = 0x00000049;

// Invalid Destination address TON
constexpr int ESME_RINVDSTTON = 0x00000050;

// Invalid Destination address NPI
constexpr int ESME_RINVDSTNPI = 0x00000051;

// 0x00000052 Reserved

// Invalid system_type field
constexpr int ESME_RINVSYSTYP = 0x00000053;

// Invalid replace_if_present flag
constexpr int ESME_RINVREPFLAG = 0x00000054;

// Invalid number of messages
constexpr int ESME_RINVNUMMSGS = 0x00000055;

// 0x00000056-0x00000057 Reserved

// Throttling error (ESME has exceeded allowed message limits)
constexpr int ESME_RTHROTTLED = 0x00000058;

// 0x00000059-0x00000060 Reserved

// Invalid Scheduled Delivery Time
constexpr int ESME_RINVSCHED = 0x00000061;

// Invalid message validity period (Expiry time)
constexpr int ESME_RINVEXPIRY = 0x00000062;

// Predefined Message Invalid or Not Found
constexpr int ESME_RINVDFTMSGID = 0x00000063;

// ESME Receiver Temporary App Error Code
constexpr int ESME_RX_T_APPN = 0x00000064;

// ESME Receiver Permanent App Error Code
constexpr int ESME_RX_P_APPN = 0x00000065;

// ESME Receiver Reject Message Error Code
constexpr int ESME_RX_R_APPN = 0x00000066;

// query_sm request failed
constexpr int ESME_RQUERYFAIL = 0x00000067;

// 0x00000068-0x000000BF Reserved

// Error in the optional part of the PDU Body.
constexpr int ESME_RINVOPTPARSTREAM = 0x000000C0;

// Optional Parameter not allowed
constexpr int ESME_ROPTPARNOTALLWD = 0x000000C1;

// Invalid Parameter Length.
constexpr int ESME_RINVPARLEN = 0x000000C2;

// Expected Optional Parameter missing
constexpr int ESME_RMISSINGOPTPARAM = 0x000000C3;

// Invalid Optional Parameter Value
constexpr int ESME_RINVOPTPARAMVAL = 0x000000C4;

// 0x000000C5-0x000000FD Reserved

// Delivery Failure (used for data_sm_resp)
constexpr int ESME_RDELIVERYFAILURE = 0x000000FE;

// Unknown Error
constexpr int ESME_RUNKNOWNERR = 0x000000FF;

// ESME Not authorised to use specified service_type
constexpr int ESME_RSERTYPUNAUTH = 0x00000100;

// ESME Prohibited from using specified operation
constexpr int ESME_RPROHIBITED = 0x00000101;

// Specified service_type is unavailable
constexpr int ESME_RSERTYPUNAVAIL = 0x00000102;

// Specified service_type is denied
constexpr int ESME_RSERTYPDENIED = 0x00000103;

// Invalid Data Coding Scheme
constexpr int ESME_RINVDCS = 0x00000104;

// Source Address Sub unit is Invalid
constexpr int ESME_RINVSRCADDRSUBUNIT = 0x00000105;

// Destination Address Sub unit is Invalid
constexpr int ESME_RINVDSTADDRSUBUNIT = 0x00000106;

// Broadcast Frequency Interval is invalid
constexpr int ESME_RINVBCASTFREQINT = 0x00000107;

// Broadcast Alias Name is invalid
constexpr int ESME_RINVBCASTALIAS_NAME = 0x00000108;

// Broadcast Area Format is invalid
constexpr int ESME_RINVBCASTAREAFMT = 0x00000109;

// Numberof Broadcast Areas is invalid
constexpr int ESME_RINVNUMBCAST_AREAS = 0x0000010A;

// Broadcast Content Type is invalid
constexpr int ESME_RINVBCASTCNTTYPE = 0x0000010B;

// Broadcast Message Class is invalid
constexpr int ESME_RINVBCASTMSGCLASS = 0x0000010C;

}  // namespace errors

}  // namespace smpp::constants

#endif
