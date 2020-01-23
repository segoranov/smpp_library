#include "smpp/smpp_client.h"

#include <algorithm>
#include <array>
#include <sstream>

#include "smpp/smpp_constants.h"
#include "smpp/smpp_exceptions.h"
#include "smpp/util/logging.h"
#include "smpp/util/serialization_util.h"

namespace smpp {

void SmppClient::checkTcpConnection() const {
  if (!m_ptrTcpSocket->is_open()) {
    throw TransportException("Socket is closed");
  }
}

void SmppClient::checkSessionState(session_util::SessionState enDesiredSessionState) const {
  if (m_enSessionState.load() != enDesiredSessionState) {
    std::stringstream error;
    error << "Invalid session state. Desired: "
          << session_util::sessionStateToString(enDesiredSessionState)
          << ". Actual: " << session_util::sessionStateToString(m_enSessionState.load());
    throw InvalidSessionStateException(error.str());
  }
}

void SmppClient::sendPdu(Pdu::Ptr pdu) {
  checkTcpConnection();

  // TODO SG: Add timer

  std::stringstream pduBuffer;
  pdu->serialize(pduBuffer);
  boost::asio::async_write(
      *m_ptrTcpSocket, boost::asio::buffer(pduBuffer.str()),
      [](boost::system::error_code ec, std::size_t length) {
        if (ec) {
          std::stringstream error;
          error << "Error code: " << ec.value() << "; error message: " << ec.message();
          throw TransportException(error.str());
        }
      });

  //   auto pduResponse = readPduResponse(pdu->getSequenceNumber(), pdu->getCommandId());
}

void SmppClient::readPduBlocking() {
//   boost::shared_array<uint8_t> commandLengthBuffer{new uint8_t[4]};
//   boost::asio::async_read(
//       *m_ptrTcpSocket, boost::asio::buffer(commandLengthBuffer.get(), 4),
//       [this, commandLengthBuffer](boost::system::error_code ec, std::size_t length) {
//         if (ec) {
//           std::stringstream error;
//           error << "Error code: " << ec.value() << "; error message: " << ec.message();
//           throw TransportException(error.str());
//         }
//         readPduBlocking(commandLengthBuffer);
//       });
}

void SmppClient::readPduBlocking(boost::shared_array<uint8_t> commandLengthBuffer) {
//   uint32_t nCommandLength = ntohl(*(reinterpret_cast<uint32_t*>(commandLengthBuffer.get())));

//   boost::shared_array<uint8_t> pduBuffer{new uint8_t[nCommandLength - 4]};

//   boost::asio::async_read(
//       *m_ptrTcpSocket, boost::asio::buffer(pduBuffer.get(), nCommandLength - 4),
//       [this, nCommandLength, pduBuffer](boost::system::error_code ec, std::size_t length) {
//         if (ec) {
//           std::stringstream error;
//           error << "Error code: " << ec.value() << "; error message: " << ec.message();
//           throw TransportException(error.str());
//         }

//         std::stringstream ssPdu;
//         binary::serializeInt32(nCommandLength, ssPdu);
//         for (int byte = 0; byte < nCommandLength - 4; byte++) {
//           binary::serializeInt8(pduBuffer[byte], ssPdu);
//         }

//         m_pduResp
//         m_pduResponseQueue.push_back(Pdu::deserialize(ssPdu));
//       });
}

Pdu::Ptr SmppClient::readPduResponse(uint32_t nSequenceNumber, uint32_t nCommandId) {
  //   uint32_t responseCommandId = smpp::constants::CMD_ID_GENERIC_NACK | nCommandId;

  //   auto itResponse = std::find_if(m_pduResponseQueue.begin(), m_pduResponseQueue.end(),
  //                                  [&](Pdu::Ptr pdu) {
  //                                    return pdu->getSequenceNumber() == nSequenceNumber &&
  //                                           pdu->getCommandId() == responseCommandId;
  //                                  });

  //   if (itResponse != m_pduResponseQueue.end()) {
  //     auto pduResponse = std::move(*itResponse);
  //     m_pduResponseQueue.erase(itResponse);
  //     return pduResponse;
  //   }

  //   while (true) {
  //     PDU pdu = readPdu(true);

  //     if (!pdu.null) {
  //       if ((pdu.getSequenceNo() == sequence &&
  //            (pdu.getCommandId() == response || pdu.getCommandId() == GENERIC_NACK)) ||
  //           (pdu.getSequenceNo() == 0 && pdu.getCommandId() == GENERIC_NACK)) {
  //         return pdu;
  //       }
  //     }
  //   }

  //   PDU pdu;
  //   return pdu;
}

Pdu::Ptr SmppClient::readPdu(bool bSynchronous) {

}

}  // namespace smpp