#ifndef SMPP_CONSTANTS_H
#define SMPP_CONSTANTS_H

#include <string>
#include <unordered_map>
#include <vector>

namespace smpp::constants {
//
// SMPP Data Types
//
constexpr int DATA_TYPE_C_OCTET_STRING = 0;
constexpr int DATA_TYPE_OCTET_STRING = 1;
constexpr int DATA_TYPE_INTEGER = 2;

constexpr int PDU_HEADER_FIELD_LENGTH = 4;
constexpr int PDU_HEADER_LENGTH = 16;
constexpr int PDU_CMD_ID_RESP_MASK = 0x80000000;  // 31st bit set to true
// constexpr Address EMPTY_ADDRESS = new Address();

constexpr uint16_t VERSION_3_3 = 0x33;
constexpr uint16_t VERSION_3_4 = 0x34;
constexpr uint16_t VERSION_5_0 = 0x50;

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

//
// SUBMIT_MULTI destination type flags
//
// constexpr int SME_ADDRESS = 1;
// constexpr int DISTRIBUTION_LIST_NAME = 2;

//
// SMPP Command ID (Requests)
//
constexpr int CMD_ID_BIND_RECEIVER = 0x00000001;
constexpr int CMD_ID_BIND_TRANSMITTER = 0x00000002;
constexpr int CMD_ID_QUERY_SM = 0x00000003;
constexpr int CMD_ID_SUBMIT_SM = 0x00000004;
constexpr int CMD_ID_DELIVER_SM = 0x00000005;
constexpr int CMD_ID_UNBIND = 0x00000006;
constexpr int CMD_ID_REPLACE_SM = 0x00000007;
constexpr int CMD_ID_CANCEL_SM = 0x00000008;
constexpr int CMD_ID_BIND_TRANSCEIVER = 0x00000009;
constexpr int CMD_ID_OUTBIND = 0x0000000B;
constexpr int CMD_ID_ENQUIRE_LINK = 0x00000015;
constexpr int CMD_ID_SUBMIT_MULTI = 0x00000021;
constexpr int CMD_ID_ALERT_NOTIFICATION = 0x00000102;
constexpr int CMD_ID_DATA_SM = 0x00000103;
constexpr int CMD_ID_BROADCAST_SM = 0x00000111;
constexpr int CMD_ID_QUERY_BROADCAST_SM = 0x00000112;
constexpr int CMD_ID_CANCEL_BROADCAST_SM = 0x00000113;

//
// SMPP Command ID (Responses)
//
constexpr int CMD_ID_GENERIC_NACK = 0x80000000;
constexpr int CMD_ID_BIND_RECEIVER_RESP = 0x80000001;
constexpr int CMD_ID_BIND_TRANSMITTER_RESP = 0x80000002;
constexpr int CMD_ID_QUERY_SM_RESP = 0x80000003;
constexpr int CMD_ID_SUBMIT_SM_RESP = 0x80000004;
constexpr int CMD_ID_DELIVER_SM_RESP = 0x80000005;
constexpr int CMD_ID_UNBIND_RESP = 0x80000006;
constexpr int CMD_ID_REPLACE_SM_RESP = 0x80000007;
constexpr int CMD_ID_CANCEL_SM_RESP = 0x80000008;
constexpr int CMD_ID_BIND_TRANSCEIVER_RESP = 0x80000009;
constexpr int CMD_ID_ENQUIRE_LINK_RESP = 0x80000015;
constexpr int CMD_ID_SUBMIT_MULTI_RESP = 0x80000021;
constexpr int CMD_ID_DATA_SM_RESP = 0x80000103;
constexpr int CMD_ID_BROADCAST_SM_RESP = 0x80000111;
constexpr int CMD_ID_QUERY_BROADCAST_SM_RESP = 0x80000112;
constexpr int CMD_ID_CANCEL_BROADCAST_SM_RESP = 0x80000113;

//
// Optional TLV Tags
//
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
constexpr uint16_t TAG_ADDITIONAL_STATUS_INFO_TEXT = 0x001D;
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

//
// SMPP Data Coding
//
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

//
// Standard SMPP Error Codes
//
/** 0x00000000: No Error */
constexpr int STATUS_OK = 0x00000000;

/** Message Length is invalid */
constexpr int STATUS_INVMSGLEN = 0x00000001;

/** Command Length is invalid */
constexpr int STATUS_INVCMDLEN = 0x00000002;

// Invalid Command ID
constexpr int STATUS_INVCMDID = 0x00000003;
// Incorrect BIND Status for given command
constexpr int STATUS_INVBNDSTS = 0x00000004;
// ESME Already in Bound State
constexpr int STATUS_ALYBND = 0x00000005;
// Invalid Priority Flag
constexpr int STATUS_INVPRTFLG = 0x00000006;
// Invalid Registered Delivery Flag
constexpr int STATUS_INVREGDLVFLG = 0x00000007;
// System Error
constexpr int STATUS_SYSERR = 0x00000008;

// 0x00000009 Reserved

// Invalid Source Address
constexpr int STATUS_INVSRCADR = 0x0000000A;
// Invalid Dest Addr
constexpr int STATUS_INVDSTADR = 0x0000000B;
// Message ID is invalid
constexpr int STATUS_INVMSGID = 0x0000000C;
// Bind Failed
constexpr int STATUS_BINDFAIL = 0x0000000D;
// Invalid Password
constexpr int STATUS_INVPASWD = 0x0000000E;
// Invalid System ID
constexpr int STATUS_INVSYSID = 0x0000000F;

// 0x00000010 Reserved

// Cancel SM Failed
constexpr int STATUS_CANCELFAIL = 0x00000011;

// 0x00000012 Reserved

// Replace SM Failed
constexpr int STATUS_REPLACEFAIL = 0x00000013;
// Message Queue Full
constexpr int STATUS_MSGQFUL = 0x00000014;
// Invalid Service Type
constexpr int STATUS_INVSERTYP = 0x00000015;

// 0x00000016-0x00000032 Reserved

// Invalid number of destinations
constexpr int STATUS_INVNUMDESTS = 0x00000033;
// Invalid Distribution List name
constexpr int STATUS_INVDLNAME = 0x00000034;

// 0x00000035-0x0000003F Reserved

// Destination flag is invalid (submit_multi)
constexpr int STATUS_INVDESTFLAG = 0x00000040;

// 0x00000041 Reserved

// Invalid ‘submit with replace’ request
// (i.e. submit_sm with replace_if_present_flag set)
constexpr int STATUS_INVSUBREP = 0x00000042;
// Invalid esm_class field data
constexpr int STATUS_INVESMCLASS = 0x00000043;
// Cannot Submit to Distribution List
constexpr int STATUS_CNTSUBDL = 0x00000044;
// submit_sm or submit_multi failed
constexpr int STATUS_SUBMITFAIL = 0x00000045;

// 0x00000046-0x00000047 Reserved

// Invalid Source address TON
constexpr int STATUS_INVSRCTON = 0x00000048;
// Invalid Source address NPI
constexpr int STATUS_INVSRCNPI = 0x00000049;
// Invalid Destination address TON
constexpr int STATUS_INVDSTTON = 0x00000050;
// Invalid Destination address NPI
constexpr int STATUS_INVDSTNPI = 0x00000051;

// 0x00000052 Reserved

// Invalid system_type field
constexpr int STATUS_INVSYSTYP = 0x00000053;
// Invalid replace_if_present flag
constexpr int STATUS_INVREPFLAG = 0x00000054;
// Invalid number of messages
constexpr int STATUS_INVNUMMSGS = 0x00000055;

// 0x00000056-0x00000057 Reserved

// Throttling error (ESME has exceeded allowed message limits)
constexpr int STATUS_THROTTLED = 0x00000058;

// 0x00000059-0x00000060 Reserved

// Invalid Scheduled Delivery Time
constexpr int STATUS_INVSCHED = 0x00000061;
// Invalid message validity period (Expiry time)
constexpr int STATUS_INVEXPIRY = 0x00000062;
// Predefined Message Invalid or Not Found
constexpr int STATUS_INVDFTMSGID = 0x00000063;
// ESME Receiver Temporary App Error Code
constexpr int STATUS_X_T_APPN = 0x00000064;
// ESME Receiver Permanent App Error Code
constexpr int STATUS_X_P_APPN = 0x00000065;
// ESME Receiver Reject Message Error Code
constexpr int STATUS_X_R_APPN = 0x00000066;
// query_sm request failed
constexpr int STATUS_QUERYFAIL = 0x00000067;

// 0x00000068-0x000000BF Reserved

// Error in the optional part of the PDU Body.
constexpr int STATUS_INVOPTPARSTREAM = 0x000000C0;
// Optional Parameter not allowed
constexpr int STATUS_OPTPARNOTALLWD = 0x000000C1;
// Invalid Parameter Length.
constexpr int STATUS_INVPARLEN = 0x000000C2;
// Expected Optional Parameter missing
constexpr int STATUS_MISSINGOPTPARAM = 0x000000C3;
// Invalid Optional Parameter Value
constexpr int STATUS_INVOPTPARAMVAL = 0x000000C4;

// 0x000000C5-0x000000FD Reserved

// Delivery Failure (used for data_sm_resp)
constexpr int STATUS_DELIVERYFAILURE = 0x000000FE;
// Unknown Error
constexpr int STATUS_UNKNOWNERR = 0x000000FF;
// ESME Not authorised to use specified service_type
constexpr int STATUS_SERTYPUNAUTH = 0x00000100;
// ESME Prohibited from using specified operation
constexpr int STATUS_PROHIBITED = 0x00000101;
// Specified service_type is unavailable
constexpr int STATUS_SERTYPUNAVAIL = 0x00000102;
// Specified service_type is denied
constexpr int STATUS_SERTYPDENIED = 0x00000103;
// Invalid Data Coding Scheme
constexpr int STATUS_INVDCS = 0x00000104;
// Source Address Sub unit is Invalid
constexpr int STATUS_INVSRCADDRSUBUNIT = 0x00000105;
// Destination Address Sub unit is Invalid
constexpr int STATUS_INVDSTADDRSUBUNIT = 0x00000106;
// Broadcast Frequency Interval is invalid
constexpr int STATUS_INVBCASTFREQINT = 0x00000107;
// Broadcast Alias Name is invalid
constexpr int STATUS_INVBCASTALIAS_NAME = 0x00000108;
// Broadcast Area Format is invalid
constexpr int STATUS_INVBCASTAREAFMT = 0x00000109;
// Numberof Broadcast Areas is invalid
constexpr int STATUS_INVNUMBCAST_AREAS = 0x0000010A;
// Broadcast Content Type is invalid
constexpr int STATUS_INVBCASTCNTTYPE = 0x0000010B;
// Broadcast Message Class is invalid
constexpr int STATUS_INVBCASTMSGCLASS = 0x0000010C;

const std::unordered_map<int, std::string> STATUS_MESSAGE_MAP{
    {STATUS_OK, "OK"},
    {STATUS_INVMSGLEN, "Message length invalid"},
    {STATUS_INVCMDLEN, "Command length invalid"},
    {STATUS_INVCMDID, "Command ID invalid"},
    {STATUS_INVBNDSTS, "Incorrect bind status for given command"},
    {STATUS_ALYBND, "ESME already in bound state"},
    {STATUS_INVPRTFLG, "Priority flag invalid"},
    {STATUS_INVREGDLVFLG, "Registered delivery flag invalid"},
    {STATUS_SYSERR, "System error"},
    {STATUS_INVSRCADR, "Source address invalid"},
    {STATUS_INVDSTADR, "Dest address invalid"},
    {STATUS_INVMSGID, "Message ID invalid"},
    {STATUS_BINDFAIL, "Bind failed"},
    {STATUS_INVPASWD, "Password invalid"},
    {STATUS_INVSYSID, "System ID invalid"},
    {STATUS_CANCELFAIL, "Cancel SM failed"},
    {STATUS_REPLACEFAIL, "Replace SM failed"},
    {STATUS_MSGQFUL, "Message queue full"},
    {STATUS_INVSERTYP, "Service type invalid"},
    {STATUS_INVNUMDESTS, "Number of destinations invalid"},
    {STATUS_INVDLNAME, "Distribution list name invalid"},
    {STATUS_INVDESTFLAG, "Destination flag is invalid"},
    {STATUS_INVSUBREP, "Submit with replace request invalid"},
    {STATUS_INVESMCLASS, "Field esm_class invalid"},
    {STATUS_CNTSUBDL, "Cannot submit to distribution list"},
    {STATUS_SUBMITFAIL, "Submit SM failed"},
    {STATUS_INVSRCTON, "Source address TON invalid"},
    {STATUS_INVSRCNPI, "Source address NPI invalid"},
    {STATUS_INVDSTTON, "Dest address TON invalid"},
    {STATUS_INVDSTNPI, "Dest address NPI invalid"},
    {STATUS_INVSYSTYP, "System type invalid"},
    {STATUS_INVREPFLAG, "Field replace_if_present invalid"},
    {STATUS_INVNUMMSGS, "Number of messages invalid"},
    {STATUS_THROTTLED, "Throttling error"},
    {STATUS_INVSCHED, "Scheduled delivery time invalid"},
    {STATUS_INVEXPIRY, "Message validity period invalid"},
    {STATUS_INVDFTMSGID, "Predefined message invalid or not found"},
    {STATUS_X_T_APPN, "ESME receiver temporary app error"},
    {STATUS_X_P_APPN, "ESME receiver permanent app error"},
    {STATUS_X_R_APPN, "ESME receiver reject app error"},
    {STATUS_QUERYFAIL, "Query SM failed"},
    {STATUS_INVOPTPARSTREAM, "Error in the optional part of the PDU Body"},
    {STATUS_OPTPARNOTALLWD, "Optional Parameter not allowed"},
    {STATUS_INVPARLEN, "Parameter length invalid"},
    {STATUS_MISSINGOPTPARAM, "Expected optional parameter missing"},
    {STATUS_INVOPTPARAMVAL, "Optional parameter value invalid"},
    {STATUS_DELIVERYFAILURE, "Deliver SM failed"},
    {STATUS_UNKNOWNERR, "Unknown error"},
    {STATUS_SERTYPUNAUTH, "Not authorised to use specified service_type"},
    {STATUS_PROHIBITED, "Prohibited from using specified operation"},
    {STATUS_SERTYPUNAVAIL, "Specified service_type is unavailable"},
    {STATUS_SERTYPDENIED, "Specified service_type is denied"},
    {STATUS_INVDCS, "Invalid Data Coding Scheme"},
    {STATUS_INVSRCADDRSUBUNIT, "Source Address Sub unit is Invalid"},
    {STATUS_INVDSTADDRSUBUNIT, "Destination Address Sub unit is Invalid"},
    {STATUS_INVBCASTFREQINT, "Broadcast Frequency Interval is invalid"},
    {STATUS_INVBCASTALIAS_NAME, "Broadcast Alias Name is invalid"},
    {STATUS_INVBCASTAREAFMT, "Broadcast Area Format is invalid"},
    {STATUS_INVNUMBCAST_AREAS, "Number of Broadcast Areas is invalid"},
    {STATUS_INVBCASTCNTTYPE, "Broadcast Content Type is invalid"},
    {STATUS_INVBCASTMSGCLASS, "Broadcast Message Class is invalid"}};

const std::unordered_map<uint16_t, std::string> TAG_NAME_MAP{
    {TAG_DEST_ADDR_SUBUNIT, "TAG_DEST_ADDR_SUBUNIT"},
    {TAG_DEST_NETWORK_TYPE, "TAG_DEST_NETWORK_TYPE"},
    {TAG_DEST_BEARER_TYPE, "TAG_DEST_BEARER_TYPE"},
    {TAG_DEST_TELEMATICS_ID, "TAG_DEST_TELEMATICS_ID"},
    {TAG_SOURCE_ADDR_SUBUNIT, "TAG_SOURCE_ADDR_SUBUNIT"},
    {TAG_SOURCE_NETWORK_TYPE, "TAG_SOURCE_NETWORK_TYPE"},
    {TAG_SOURCE_BEARER_TYPE, "TAG_SOURCE_BEARER_TYPE"},
    {TAG_SOURCE_TELEMATICS_ID, "TAG_SOURCE_TELEMATICS_ID"},
    {TAG_QOS_TIME_TO_LIVE, "TAG_QOS_TIME_TO_LIVE"},
    {TAG_PAYLOAD_TYPE, "TAG_PAYLOAD_TYPE"},
    {TAG_ADDITIONAL_STATUS_INFO_TEXT, "TAG_ADDITIONAL_STATUS_INFO_TEXT"},
    {TAG_RECEIPTED_MESSAGE_ID, "TAG_RECEIPTED_MESSAGE_ID"},
    {TAG_MS_MSG_WAIT_FACILITIES, "TAG_MS_MSG_WAIT_FACILITIES"},
    {TAG_PRIVACY_INDICATOR, "TAG_PRIVACY_INDICATOR"},
    {TAG_SOURCE_SUBADDRESS, "TAG_SOURCE_SUBADDRESS"},
    {TAG_DEST_SUBADDRESS, "TAG_DEST_SUBADDRESS"},
    {TAG_USER_MESSAGE_REFERENCE, "TAG_USER_MESSAGE_REFERENCE"},
    {TAG_USER_RESPONSE_CODE, "TAG_USER_RESPONSE_CODE"},
    {TAG_SOURCE_PORT, "TAG_SOURCE_PORT"},
    {TAG_DEST_PORT, "TAG_DEST_PORT"},
    {TAG_SAR_MSG_REF_NUM, "TAG_SAR_MSG_REF_NUM"},
    {TAG_LANGUAGE_INDICATOR, "TAG_LANGUAGE_INDICATOR"},
    {TAG_SAR_TOTAL_SEGMENTS, "TAG_SAR_TOTAL_SEGMENTS"},
    {TAG_SAR_SEGMENT_SEQNUM, "TAG_SAR_SEGMENT_SEQNUM"},
    {TAG_SC_INTERFACE_VERSION, "TAG_SC_INTERFACE_VERSION"},
    {TAG_CALLBACK_NUM_PRES_IND, "TAG_CALLBACK_NUM_PRES_IND"},
    {TAG_CALLBACK_NUM_ATAG, "TAG_CALLBACK_NUM_ATAG"},
    {TAG_NUMBER_OF_MESSAGES, "TAG_NUMBER_OF_MESSAGES"},
    {TAG_CALLBACK_NUM, "TAG_CALLBACK_NUM"},
    {TAG_DPF_RESULT, "TAG_DPF_RESULT"},
    {TAG_SET_DPF, "TAG_SET_DPF"},
    {TAG_MS_AVAILABILITY_STATUS, "TAG_MS_AVAILABILITY_STATUS"},
    {TAG_NETWORK_ERROR_CODE, "TAG_NETWORK_ERROR_CODE"},
    {TAG_MESSAGE_PAYLOAD, "TAG_MESSAGE_PAYLOAD"},
    {TAG_DELIVERY_FAILURE_REASON, "TAG_DELIVERY_FAILURE_REASON"},
    {TAG_MORE_MESSAGES_TO_SEND, "TAG_MORE_MESSAGES_TO_SEND"},
    {TAG_MESSAGE_STATE, "TAG_MESSAGE_STATE"},
    {TAG_USSD_SERVICE_OP, "TAG_USSD_SERVICE_OP"},
    {TAG_DISPLAY_TIME, "TAG_DISPLAY_TIME"},
    {TAG_SMS_SIGNAL, "TAG_SMS_SIGNAL"},
    {TAG_MS_VALIDITY, "TAG_MS_VALIDITY"},
    {TAG_ALERT_ON_MESSAGE_DELIVERY, "TAG_ALERT_ON_MESSAGE_DELIVERY"},
    {TAG_ITS_REPLY_TYPE, "TAG_ITS_REPLY_TYPE"},
    {TAG_ITS_SESSION_INFO, "TAG_ITS_SESSION_INFO"}};

}  // namespace smpp::constants

#endif