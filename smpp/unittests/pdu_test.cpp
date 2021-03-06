#include <sstream>

#include "catch.hpp"
#include "smpp/commands.h"
#include "smpp/smpp_constants.h"
#include "smpp/smpp_exceptions.h"
#include "smpp/util/print_util.h"
#include "smpp/util/smpp_util.h"

SCENARIO("Pdu is serialized/deserialized properly", "[pdu]") {
  GIVEN("A sample BindTransmitter pdu defined as raw data (array of hex bytes)") {
    /*
    Sample PDU (Values are shown in Hex format):
    00 00 00 2F 00 00 00 02 00 00 00 00 00 00 00 01
    53 4D 50 50 33 54 45 53 54 00 73 65 63 72 65 74
    30 38 00 53 55 42 4D 49 54 31 00 50 01 01 00

    The 16-octet header would be decoded as follows:
    00 00 00 2F Command Length 0x0000002F (47 in decimal)
    00 00 00 02 Command ID 0x00000002 (id of bind transmitter)
    00 00 00 00 Command Status 0x00000000
    00 00 00 01 Sequence Number 0x00000001

    The remaining data represents the PDU body (which in this example relates to the
    bind_transmitter PDU).
    This is diagnosed as follows:
    53 4D 50 50 33 54 45 53 54 00       system_id (“SMPP3TEST”)
    73 65 63 72 65 74 30 38 00          password (“secret08”)
    53 55 42 4D 49 54 31 00             system_type (“SUBMIT1”)
    50                                  interface_version (0x50 “V5.0 compliant”)
    01                                  addr_ton (0x01)
    01                                  addr_npi (0x01)
    00                                  addr_range (NULL)
    */

    const uint8_t samplePdu[] = {0x00, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x53, 0x4D, 0x50, 0x50,
                                 0x33, 0x54, 0x45, 0x53, 0x54, 0x00, 0x73, 0x65, 0x63, 0x72,
                                 0x65, 0x74, 0x30, 0x38, 0x00, 0x53, 0x55, 0x42, 0x4D, 0x49,
                                 0x54, 0x31, 0x00, 0x50, 0x01, 0x01, 0x00};

    THEN("The size of the sample pdu should be 47") { REQUIRE(sizeof(samplePdu) == 47); }

    AND_GIVEN("a BindTransmitter PDU corresponding to the raw PDU") {
      smpp::BindTransmitter bindTransmitterPdu{
          smpp::builder::BindBuilder()
              .withSequenceNumber(1)
              .withSystemId("SMPP3TEST")
              .withPassword("secret08")
              .withSystemType("SUBMIT1")
              .withInterfaceVersion(0x50)
              .withAddrTon(0x01)
              .withAddrNpi(0x01)
              .withAddressRange(smpp::constants::null_settings::NULL_C_OCTET_STRING)};

      THEN("the command length of the PDU should be 47") {
        REQUIRE(bindTransmitterPdu.getCommandLength() == 47);
      }

      WHEN("the BindTransmitter PDU is serialized into a stringstream") {
        std::stringstream ss;
        bindTransmitterPdu.serialize(ss);

        THEN("the stringstream size should be 47 bytes (the command length)") {
          REQUIRE(ss.str().size() == 47);
        }

        THEN(
            "the string from the stringstream should be equal to the string created by the raw "
            "PDU") {
          REQUIRE(ss.str() == std::string{(char*)samplePdu, sizeof(samplePdu)});
        }

        AND_WHEN("a BindTransmitter PDU is deserialized from the stringstream") {
          smpp::Pdu::SPtr deserializedPdu = smpp::Pdu::deserialize(ss);
          auto deserializedBindTransmitterPdu = deserializedPdu->asBindTransmitter();
          REQUIRE(deserializedBindTransmitterPdu);

          THEN("the deserialized PDU should correspond to the initial PDU") {
            REQUIRE(deserializedBindTransmitterPdu->equals(bindTransmitterPdu));
          }
        }
      }
    }
  }

  GIVEN("A sample BindTransmitterResp pdu defined as raw data (array of hex bytes)") {
    /*
    Sample PDU (Values are shown in Hex format):
    00 00 00 2F 80 00 00 02 00 00 00 00 00 00 00 01
    53 4D 50 50 33 54 45 53 54 00 02 10 00 01 01

    The 16-octet header would be decoded as follows:
    00 00 00 1F Command Length 0x0000002F (31 in decimal)
    80 00 00 02 Command ID 0x80000002 (id of bind transmitter resp)
    00 00 00 00 Command Status 0x00000000
    00 00 00 01 Sequence Number 0x00000001

    The remaining data represents the PDU body (which in this example relates to the
    bind_transmitter_resp PDU).
    This is diagnosed as follows:
    53 4D 50 50 33 54 45 53 54 00       system_id (“SMPP3TEST”)
    02 10                               TLV sc_interface_version tag
    00 01                               TLV sc_interface_version length
    50                                  TLV sc_interface_version value
    */

    const uint8_t samplePdu[] = {0x00, 0x00, 0x00, 0x1F, 0x80, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
                                 0x00, 0x00, 0x00, 0x00, 0x01, 0x53, 0x4D, 0x50, 0x50, 0x33, 0x54,
                                 0x45, 0x53, 0x54, 0x00, 0x02, 0x10, 0x00, 0x01, 0x50};

    THEN("The size of the sample pdu should be 31") { REQUIRE(sizeof(samplePdu) == 31); }

    AND_GIVEN("a BindTransmitterResp PDU corresponding to the raw PDU") {
      smpp::BindTransmitterResp bindTransmitterRespPdu{
          smpp::builder::BindRespBuilder()
              .withCommandStatus(smpp::constants::command_status::ESME_ROK)
              .withSequenceNumber(1)
              .withSystemId("SMPP3TEST")
              .withScInterfaceVersion(smpp::constants::VERSION_5_0)};

      THEN("the command length of the PDU should be 31") {
        REQUIRE(bindTransmitterRespPdu.getCommandLength() == 31);
      }

      WHEN("the BindTransmitterResp PDU is serialized into a stringstream") {
        std::stringstream ss;
        bindTransmitterRespPdu.serialize(ss);

        THEN("the stringstream size should be 31 bytes (the command length)") {
          REQUIRE(ss.str().size() == 31);
        }

        THEN(
            "the string from the stringstream should be equal to the string created by the raw "
            "PDU") {
          REQUIRE(ss.str() == std::string{(char*)samplePdu, sizeof(samplePdu)});
        }

        AND_WHEN("a BindTransmitterResp PDU is deserialized from the stringstream") {
          smpp::Pdu::SPtr deserializedPdu = smpp::Pdu::deserialize(ss);
          auto deserializedBindTransmitterRespPdu = deserializedPdu->asBindTransmitterResp();
          REQUIRE(deserializedBindTransmitterRespPdu);
          REQUIRE(deserializedBindTransmitterRespPdu->hasOptionalParameter(
              smpp::constants::TAG_SC_INTERFACE_VERSION));

          THEN("the deserialized PDU should correspond to the initial PDU") {
            REQUIRE(deserializedBindTransmitterRespPdu->getCommandLength() ==
                    bindTransmitterRespPdu.getCommandLength());

            REQUIRE(deserializedBindTransmitterRespPdu->getCommandStatus() ==
                    bindTransmitterRespPdu.getCommandStatus());

            REQUIRE(deserializedBindTransmitterRespPdu->getSequenceNumber() ==
                    bindTransmitterRespPdu.getSequenceNumber());

            REQUIRE(deserializedBindTransmitterRespPdu->getSystemId() ==
                    bindTransmitterRespPdu.getSystemId());

            REQUIRE(deserializedBindTransmitterRespPdu->getOptionalParameters().size() == 1);
            REQUIRE(deserializedBindTransmitterRespPdu->getOptionalParameters()[0] ==
                    smpp::Tlv{smpp::constants::TAG_SC_INTERFACE_VERSION,
                              smpp::constants::VERSION_5_0});
          }
        }
      }
    }
  }

  GIVEN("A sample submit sm pdu with size 44 bytes") {
    smpp::SubmitSm submitSmPdu{
        smpp::builder::SubmitSmBuilder()
            .withSequenceNumber(378019)
            .withServiceType("A")
            .withSourceAddrTon(0x03)
            .withSourceAddrNpi(0x01)
            .withSourceAddr("B")
            .withDestAddrTon(0x03)
            .withDestAddrNpi(0x01)
            .withDestinationAddr("C")
            .withEsmClass(smpp::constants::null_settings::NULL_INT8)
            .withProtocolId(smpp::constants::null_settings::NULL_INT8)
            .withPriorityFlag(smpp::constants::null_settings::NULL_INT8)
            .withScheduleDeliveryTime(smpp::constants::null_settings::NULL_C_OCTET_STRING)
            .withValidityPeriod("D")
            .withRegisteredDelivery(0x01)
            .withReplaceIfPresentFlag(smpp::constants::null_settings::NULL_INT8)
            .withDataCoding(smpp::constants::null_settings::NULL_INT8)
            .withSmDefaultMsgId(smpp::constants::null_settings::NULL_INT8)
            .withShortMessage("TEST_SM")};

    THEN("the command length of the PDU should be 44") {
      REQUIRE(submitSmPdu.getCommandLength() == 44);
    }

    WHEN("the submit sm PDU is serialized into a stringstream") {
      std::stringstream ss;
      submitSmPdu.serialize(ss);

      THEN("the stringstream size should be 44 bytes (the command length)") {
        REQUIRE(ss.str().size() == 44);
      }

      AND_WHEN("a submit sm PDU is deserialized from the stringstream") {
        smpp::Pdu::SPtr deserializedPdu = smpp::Pdu::deserialize(ss);
        auto deserializedSubmitSmPdu = deserializedPdu->asSubmitSm();
        REQUIRE(deserializedSubmitSmPdu);

        THEN("the deserialized PDU should correspond to the initial PDU") {
          // test the same thing in different ways to make sure everything is OK
          REQUIRE(deserializedPdu->equals(submitSmPdu));
          REQUIRE(deserializedSubmitSmPdu->equals(submitSmPdu));
          REQUIRE(submitSmPdu.equals(*deserializedPdu));
        }
      }
    }
  }

  GIVEN("A sample deliver sm pdu with size 44 bytes") {
    smpp::DeliverSm deliverSmPdu{
        smpp::builder::DeliverSmBuilder()
            .withSequenceNumber(378019)
            .withServiceType("A")
            .withSourceAddrTon(0x03)
            .withSourceAddrNpi(0x01)
            .withSourceAddr("B")
            .withDestAddrTon(0x03)
            .withDestAddrNpi(0x01)
            .withDestinationAddr("C")
            .withEsmClass(smpp::constants::null_settings::NULL_INT8)
            .withProtocolId(smpp::constants::null_settings::NULL_INT8)
            .withPriorityFlag(smpp::constants::null_settings::NULL_INT8)
            .withScheduleDeliveryTime(smpp::constants::null_settings::NULL_C_OCTET_STRING)
            .withValidityPeriod("D")
            .withRegisteredDelivery(0x01)
            .withReplaceIfPresentFlag(smpp::constants::null_settings::NULL_INT8)
            .withDataCoding(smpp::constants::null_settings::NULL_INT8)
            .withSmDefaultMsgId(smpp::constants::null_settings::NULL_INT8)
            .withShortMessage("TEST_DM")};

    THEN("the command length of the PDU should be 44") {
      REQUIRE(deliverSmPdu.getCommandLength() == 44);
    }

    WHEN("the deliver sm PDU is serialized into a stringstream") {
      std::stringstream ss;
      deliverSmPdu.serialize(ss);

      THEN("the stringstream size should be 44 bytes (the command length)") {
        REQUIRE(ss.str().size() == 44);
      }

      AND_WHEN("a deliverSmPdu sm PDU is deserialized from the stringstream") {
        smpp::Pdu::SPtr deserializedPdu = smpp::Pdu::deserialize(ss);
        auto deserializedDeliverSmPdu = deserializedPdu->asDeliverSm();
        REQUIRE(deserializedDeliverSmPdu);

        THEN("the deserialized PDU should correspond to the initial PDU") {
          // test the same thing in different ways to make sure everything is OK
          REQUIRE(deserializedDeliverSmPdu->equals(deliverSmPdu));
          REQUIRE(deliverSmPdu.equals(*deserializedDeliverSmPdu));
        }
      }
    }
  }

  GIVEN("A sample submit sm resp pdu with size 28 bytes") {
    smpp::SubmitSmResp submitSmRespPdu{
        smpp::builder::SubmitSmRespBuilder()
            .withCommandStatus(smpp::constants::command_status::ESME_ROK)
            .withSequenceNumber(378019)
            .withMessageId("0118Z-01026")};

    THEN("the command length of the PDU should be 28") {
      REQUIRE(submitSmRespPdu.getCommandLength() == 28);
    }

    WHEN("the submit sm resp PDU is serialized into a stringstream") {
      std::stringstream ss;
      submitSmRespPdu.serialize(ss);

      THEN("the stringstream size should be 28 bytes (the command length)") {
        REQUIRE(ss.str().size() == 28);
      }

      AND_WHEN("a submit sm resp PDU is deserialized from the stringstream") {
        smpp::Pdu::SPtr deserializedPdu = smpp::Pdu::deserialize(ss);
        auto deserializedSubmitSmRespPdu = deserializedPdu->asSubmitSmResp();
        REQUIRE(deserializedSubmitSmRespPdu);

        THEN("the deserialized PDU should correspond to the initial PDU") {
          REQUIRE(deserializedSubmitSmRespPdu->getCommandLength() ==
                  submitSmRespPdu.getCommandLength());
          REQUIRE(deserializedSubmitSmRespPdu->getCommandStatus() ==
                  submitSmRespPdu.getCommandStatus());
          REQUIRE(deserializedSubmitSmRespPdu->getSequenceNumber() ==
                  submitSmRespPdu.getSequenceNumber());
          REQUIRE(deserializedSubmitSmRespPdu->getMessageId() == submitSmRespPdu.getMessageId());
          REQUIRE(deserializedSubmitSmRespPdu->getOptionalParameters().size() == 0);
        }
      }
    }
  }

  GIVEN("A sample data sm pdu with size 29 bytes") {
    smpp::DataSm dataSmPdu{smpp::builder::DataSmBuilder()
                               .withSequenceNumber(378019)
                               .withServiceType("A")
                               .withSourceAddrTon(0x03)
                               .withSourceAddrNpi(0x01)
                               .withSourceAddr("B")
                               .withDestAddrTon(0x03)
                               .withDestAddrNpi(0x01)
                               .withDestinationAddr("C")
                               .withEsmClass(smpp::constants::null_settings::NULL_INT8)
                               .withRegisteredDelivery(0x01)
                               .withDataCoding(smpp::constants::null_settings::NULL_INT8)};

    THEN("The command length of the pdu should be 29 bytes") {
      REQUIRE(dataSmPdu.getCommandLength() == 29);
    }

    WHEN("the data sm PDU is serialized into a stringstream") {
      std::stringstream ss;
      dataSmPdu.serialize(ss);

      THEN("the stringstream size should be 29 bytes (the command length)") {
        REQUIRE(ss.str().size() == 29);
      }

      AND_WHEN("a data sm PDU is deserialized from the stringstream") {
        smpp::Pdu::SPtr deserializedPdu = smpp::Pdu::deserialize(ss);
        auto deserializedDataSmPdu = deserializedPdu->asDataSm();
        REQUIRE(deserializedDataSmPdu);

        THEN("the deserialized PDU should correspond to the initial PDU") {
          REQUIRE(deserializedDataSmPdu->equals(dataSmPdu));
        }
      }
    }
  }

  GIVEN("A sample outbind pdu with size 35 bytes") {
    smpp::Outbind outbindPdu{smpp::builder::OutbindBuilder()
                                 .withSequenceNumber(378019)
                                 .withSystemId("SMPP3TEST")
                                 .withPassword("secret08")};

    THEN("The command length of the pdu should be 35 bytes") {
      REQUIRE(outbindPdu.getCommandLength() == 35);
    }

    WHEN("the outbind PDU is serialized into a stringstream") {
      std::stringstream ss;
      outbindPdu.serialize(ss);

      THEN("the stringstream size should be 35 bytes (the command length)") {
        REQUIRE(ss.str().size() == 35);
      }

      AND_WHEN("an outbind PDU is deserialized from the stringstream") {
        smpp::Pdu::SPtr deserializedPdu = smpp::Pdu::deserialize(ss);
        auto deserializedOutbindPdu = deserializedPdu->asOutbind();
        REQUIRE(deserializedOutbindPdu);

        THEN("the deserialized PDU should correspond to the initial PDU") {
          REQUIRE(deserializedOutbindPdu->equals(outbindPdu));
        }
      }
    }
  }

  GIVEN("A sample enquire link pdu with size 16 bytes") {
    smpp::EnquireLink enquireLinkPdu{
        smpp::builder::EnquireLinkBuilder().withSequenceNumber(378019)};

    THEN("The command length of the pdu should be 16 bytes") {
      REQUIRE(enquireLinkPdu.getCommandLength() == 16);
    }

    WHEN("the enquire link PDU is serialized into a stringstream") {
      std::stringstream ss;
      enquireLinkPdu.serialize(ss);

      THEN("the stringstream size should be 16 bytes (the command length)") {
        REQUIRE(ss.str().size() == 16);
      }

      AND_WHEN("an enquire link PDU is deserialized from the stringstream") {
        smpp::Pdu::SPtr deserializedPdu = smpp::Pdu::deserialize(ss);
        auto deserializedEnquireLinkPdu = deserializedPdu->asEnquireLink();
        REQUIRE(deserializedEnquireLinkPdu);

        THEN("the deserialized PDU should correspond to the initial PDU") {
          REQUIRE(deserializedEnquireLinkPdu->equals(enquireLinkPdu));
        }
      }
    }
  }

  GIVEN("A sample enquire link resp pdu with size 16 bytes") {
    smpp::EnquireLinkResp enquireLinkRespPdu{
        smpp::builder::EnquireLinkRespBuilder().withSequenceNumber(378019)};

    THEN("The command length of the pdu should be 16 bytes") {
      REQUIRE(enquireLinkRespPdu.getCommandLength() == 16);
    }

    WHEN("the enquire link resp PDU is serialized into a stringstream") {
      std::stringstream ss;
      enquireLinkRespPdu.serialize(ss);

      THEN("the stringstream size should be 16 bytes (the command length)") {
        REQUIRE(ss.str().size() == 16);
      }

      AND_WHEN("an enquire link resp PDU is deserialized from the stringstream") {
        smpp::Pdu::SPtr deserializedPdu = smpp::Pdu::deserialize(ss);
        auto deserializedEnquireLinkRespPdu = deserializedPdu->asEnquireLinkResp();
        REQUIRE(deserializedEnquireLinkRespPdu);

        THEN("the deserialized PDU should correspond to the initial PDU") {
          REQUIRE(deserializedEnquireLinkRespPdu->equals(enquireLinkRespPdu));
        }
      }
    }
  }

  GIVEN("A sample generic nack pdu with size 16 bytes") {
    smpp::GenericNack genericNackPdu{
        smpp::builder::GenericNackBuilder()
            .withCommandStatus(smpp::constants::command_status::ESME_RINVDSTTON)
            .withSequenceNumber(378019)};

    THEN("The command length of the pdu should be 16 bytes") {
      REQUIRE(genericNackPdu.getCommandLength() == 16);
    }

    WHEN("the generic nack PDU is serialized into a stringstream") {
      std::stringstream ss;
      genericNackPdu.serialize(ss);

      THEN("the stringstream size should be 16 bytes (the command length)") {
        REQUIRE(ss.str().size() == 16);
      }

      AND_WHEN("a generic nack PDU is deserialized from the stringstream") {
        smpp::Pdu::SPtr deserializedPdu = smpp::Pdu::deserialize(ss);
        auto deserializedGenericNackPdu = deserializedPdu->asGenericNack();
        REQUIRE(deserializedGenericNackPdu);

        THEN("the deserialized PDU should correspond to the initial PDU") {
          REQUIRE(deserializedGenericNackPdu->equals(genericNackPdu));
        }
      }
    }
  }

  GIVEN("A sample unbind pdu with size 16 bytes") {
    smpp::Unbind unbindPdu{smpp::builder::UnbindBuilder().withSequenceNumber(378019)};

    THEN("The command length of the pdu should be 16 bytes") {
      REQUIRE(unbindPdu.getCommandLength() == 16);
    }

    WHEN("the unbind PDU is serialized into a stringstream") {
      std::stringstream ss;
      unbindPdu.serialize(ss);

      THEN("the stringstream size should be 16 bytes (the command length)") {
        REQUIRE(ss.str().size() == 16);
      }

      AND_WHEN("an unbind PDU is deserialized from the stringstream") {
        smpp::Pdu::SPtr deserializedPdu = smpp::Pdu::deserialize(ss);
        auto deserializedUnbindPdu = deserializedPdu->asUnbind();
        REQUIRE(deserializedUnbindPdu);

        THEN("the deserialized PDU should correspond to the initial PDU") {
          REQUIRE(deserializedUnbindPdu->equals(unbindPdu));
        }
      }
    }
  }

  GIVEN("A sample unbind resp pdu with size 16 bytes") {
    smpp::UnbindResp unbindRespPdu{
        smpp::builder::UnbindRespBuilder()
            .withCommandStatus(smpp::constants::command_status::ESME_ROK)
            .withSequenceNumber(378019)};

    THEN("The command length of the pdu should be 16 bytes") {
      REQUIRE(unbindRespPdu.getCommandLength() == 16);
    }

    WHEN("the unbind resp PDU is serialized into a stringstream") {
      std::stringstream ss;
      unbindRespPdu.serialize(ss);

      THEN("the stringstream size should be 16 bytes (the command length)") {
        REQUIRE(ss.str().size() == 16);
      }

      AND_WHEN("an unbind resp PDU is deserialized from the stringstream") {
        smpp::Pdu::SPtr deserializedPdu = smpp::Pdu::deserialize(ss);
        auto deserializedUnbindRespPdu = deserializedPdu->asUnbindResp();
        REQUIRE(deserializedUnbindRespPdu);

        THEN("the deserialized PDU should correspond to the initial PDU") {
          REQUIRE(deserializedUnbindRespPdu->equals(unbindRespPdu));
        }
      }
    }
  }

  GIVEN("A sample submit multi pdu with size 119 bytes") {
    smpp::SubmitMultiDestinationAddresses destAddresses;
    destAddresses.addSMEDestAddress(
        smpp::SMEDestAddress{0x01, 0x01, "TEST1"});  // 1 + 1 + 1 + 5 + 1  = 9 bytes
    destAddresses.addSMEDestAddress(
        smpp::SMEDestAddress{0x01, 0x01, "TEST23"});  // 1 + 1 + 1 + 6 + 1  = 10 bytes
    destAddresses.addSMEDestAddress(
        smpp::SMEDestAddress{0x01, 0x01, "TEST345"});  // 1 + 1 + 1 + 7 + 1  = 11 bytes

    destAddresses.addDistributionListDestAddress(
        smpp::DistributionListDestAddress{"TEST_DLNAME_1"});  // 1 + 13 + 1 = 15 bytes
    destAddresses.addDistributionListDestAddress(
        smpp::DistributionListDestAddress{"TEST_DLNAME_23"});  // 1 + 14 + 1 = 16 bytes
    destAddresses.addDistributionListDestAddress(
        smpp::DistributionListDestAddress{"TEST_DLNAME_345"});  // 1 + 15 + 1 = 17 bytes

    /* Total size of dest addresses is 79:
        number of dests -> 1 byte
        3 SME dest addresses -> 9 + 10 + 11 = 30 bytes;
        3 Distribution list dest addresses -> 15 + 16 + 17 = 48 bytes

        Total: 1 + 30 + 48 = 79
    */

    smpp::SubmitMulti submitMultiPdu{
        smpp::builder::SubmitMultiBuilder()
            .withSequenceNumber(378019)
            .withServiceType("A")
            .withSourceAddrTon(0x03)
            .withSourceAddrNpi(0x01)
            .withSourceAddr("B")
            .withDestinationAddresses(destAddresses)  // 79 bytes
            .withEsmClass(smpp::constants::null_settings::NULL_INT8)
            .withProtocolId(smpp::constants::null_settings::NULL_INT8)
            .withPriorityFlag(smpp::constants::null_settings::NULL_INT8)
            .withScheduleDeliveryTime(smpp::constants::null_settings::NULL_C_OCTET_STRING)
            .withValidityPeriod("D")
            .withRegisteredDelivery(0x01)
            .withReplaceIfPresentFlag(smpp::constants::null_settings::NULL_INT8)
            .withDataCoding(smpp::constants::null_settings::NULL_INT8)
            .withSmDefaultMsgId(smpp::constants::null_settings::NULL_INT8)
            .withShortMessage("TEST_SM")};

    THEN("the command length of the PDU should be 119") {
      REQUIRE(submitMultiPdu.getCommandLength() == 119);
    }

    WHEN("the submit multi PDU is serialized into a stringstream") {
      std::stringstream ss;
      submitMultiPdu.serialize(ss);

      THEN("the stringstream size should be 119 bytes (the command length)") {
        REQUIRE(ss.str().size() == 119);
      }

      AND_WHEN("a submit multi PDU is deserialized from the stringstream") {
        smpp::Pdu::SPtr deserializedPdu = smpp::Pdu::deserialize(ss);
        auto deserializedSubmitMultiPdu = deserializedPdu->asSubmitMulti();
        REQUIRE(deserializedSubmitMultiPdu);

        THEN("the deserialized PDU should correspond to the initial PDU") {
          REQUIRE(deserializedSubmitMultiPdu->getCommandLength() ==
                  submitMultiPdu.getCommandLength());

          REQUIRE(deserializedSubmitMultiPdu->getCommandStatus() ==
                  submitMultiPdu.getCommandStatus());

          REQUIRE(deserializedSubmitMultiPdu->getSequenceNumber() ==
                  submitMultiPdu.getSequenceNumber());

          REQUIRE(deserializedSubmitMultiPdu->getDestinationAddresses() ==
                  submitMultiPdu.getDestinationAddresses());

          REQUIRE(deserializedSubmitMultiPdu->getShortMessage() ==
                  submitMultiPdu.getShortMessage());
          REQUIRE(deserializedSubmitMultiPdu->getOptionalParameters().size() == 0);
        }
      }
    }
  }
}

SCENARIO("Deserialiation of malformed PDUs throws proper exceptions", "[malformed_pdu]") {
  GIVEN("A stream containing invalid command id - 12 (0x00 0x00 0x00 0x0C in hex)") {
    const char rawDataPduWithInvalidCommandLength[] = {
        0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x01, 0x53, 0x4D, 0x50, 0x50, 0x33, 0x54, 0x45, 0x53,
        0x54, 0x00, 0x73, 0x65, 0x63, 0x72, 0x65, 0x74, 0x30, 0x38, 0x00, 0x53,
        0x55, 0x42, 0x4D, 0x49, 0x54, 0x31, 0x00, 0x50, 0x01, 0x01, 0x00};

    std::stringstream ss{std::string{rawDataPduWithInvalidCommandLength,
                                     sizeof(rawDataPduWithInvalidCommandLength)}};

    WHEN("We try to deserialize a PDU") {
      THEN("InvalidCommandLengthException should be thrown") {
        REQUIRE_THROWS_AS(smpp::Pdu::deserialize(ss), smpp::InvalidCommandLengthException);
      }
    }
  }

  GIVEN("A stream containing invalid command id - 0x77 0x00 0x00 0x77") {
    const char rawDataPduWithInvalidCommandId[] = {
        0x00, 0x00, 0x00, 0x2F, 0x77, 0x00, 0x00, 0x77, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x01, 0x53, 0x4D, 0x50, 0x50, 0x33, 0x54, 0x45, 0x53,
        0x54, 0x00, 0x73, 0x65, 0x63, 0x72, 0x65, 0x74, 0x30, 0x38, 0x00, 0x53,
        0x55, 0x42, 0x4D, 0x49, 0x54, 0x31, 0x00, 0x50, 0x01, 0x01, 0x00};

    std::stringstream ss{
        std::string{rawDataPduWithInvalidCommandId, sizeof(rawDataPduWithInvalidCommandId)}};

    WHEN("We try to deserialize a PDU") {
      THEN("InvalidCommandIdException should be thrown") {
        REQUIRE_THROWS_AS(smpp::Pdu::deserialize(ss), smpp::InvalidCommandIdException);
      }
    }
  }
}

SCENARIO("Comparison of Pdu's using equals() method is correct") {
  auto createTestSubmitSmPdu = [] {
    return smpp::SubmitSm{
        smpp::builder::SubmitSmBuilder()
            .withSequenceNumber(378019)
            .withServiceType("A")
            .withSourceAddrTon(0x03)
            .withSourceAddrNpi(0x01)
            .withSourceAddr("B")
            .withDestAddrTon(0x03)
            .withDestAddrNpi(0x01)
            .withDestinationAddr("C")
            .withEsmClass(smpp::constants::null_settings::NULL_INT8)
            .withProtocolId(smpp::constants::null_settings::NULL_INT8)
            .withPriorityFlag(smpp::constants::null_settings::NULL_INT8)
            .withScheduleDeliveryTime(smpp::constants::null_settings::NULL_C_OCTET_STRING)
            .withValidityPeriod("D")
            .withRegisteredDelivery(0x01)
            .withReplaceIfPresentFlag(smpp::constants::null_settings::NULL_INT8)
            .withDataCoding(smpp::constants::null_settings::NULL_INT8)
            .withSmDefaultMsgId(smpp::constants::null_settings::NULL_INT8)
            .withShortMessage("TEST_SM")};
  };

  auto createTestBindRespPdu = [] {
    return smpp::BindTransmitterResp{
        smpp::builder::BindRespBuilder()
            .withCommandStatus(smpp::constants::command_status::ESME_ROK)
            .withSequenceNumber(1)
            .withSystemId("SMPP3TEST")
            .withScInterfaceVersion(smpp::constants::VERSION_5_0)};
  };

  GIVEN("Two equal submit sm PDUs") {
    auto pdu1 = createTestSubmitSmPdu();
    auto pdu2 = createTestSubmitSmPdu();
    THEN("they should be equal") { REQUIRE(pdu1.equals(pdu2)); }
  }

  GIVEN("Two non-equal submit sm PDUs") {
    auto pdu1 = createTestSubmitSmPdu();

    // make the destination addr the only difference
    smpp::SubmitSm pdu2{
        smpp::builder::SubmitSmBuilder()
            .withSequenceNumber(378019)
            .withServiceType("A")
            .withSourceAddrTon(0x03)
            .withSourceAddrNpi(0x01)
            .withSourceAddr("B")
            .withDestAddrTon(0x03)
            .withDestAddrNpi(0x01)
            .withDestinationAddr("D")
            .withEsmClass(smpp::constants::null_settings::NULL_INT8)
            .withProtocolId(smpp::constants::null_settings::NULL_INT8)
            .withPriorityFlag(smpp::constants::null_settings::NULL_INT8)
            .withScheduleDeliveryTime(smpp::constants::null_settings::NULL_C_OCTET_STRING)
            .withValidityPeriod("D")
            .withRegisteredDelivery(0x01)
            .withReplaceIfPresentFlag(smpp::constants::null_settings::NULL_INT8)
            .withDataCoding(smpp::constants::null_settings::NULL_INT8)
            .withSmDefaultMsgId(smpp::constants::null_settings::NULL_INT8)
            .withShortMessage("TEST_SM")};
    THEN("they should not be equal") { REQUIRE_FALSE(pdu1.equals(pdu2)); }
  }

  GIVEN("A submit sm PDU and a bind PDU") {
    auto pdu1 = createTestSubmitSmPdu();
    auto pdu2 = createTestBindRespPdu();
    THEN("they should not be equal") { REQUIRE_FALSE(pdu1.equals(pdu2)); }
  }

  GIVEN("Two almost equal submit sm PDUs differing only in one optional Tlv parameter") {
    auto pdu1 = createTestSubmitSmPdu();

    smpp::SubmitSm pdu2{
        smpp::builder::SubmitSmBuilder()
            .withSequenceNumber(378019)
            .withServiceType("A")
            .withSourceAddrTon(0x03)
            .withSourceAddrNpi(0x01)
            .withSourceAddr("B")
            .withDestAddrTon(0x03)
            .withDestAddrNpi(0x01)
            .withDestinationAddr("C")
            .withEsmClass(smpp::constants::null_settings::NULL_INT8)
            .withProtocolId(smpp::constants::null_settings::NULL_INT8)
            .withPriorityFlag(smpp::constants::null_settings::NULL_INT8)
            .withScheduleDeliveryTime(smpp::constants::null_settings::NULL_C_OCTET_STRING)
            .withValidityPeriod("D")
            .withRegisteredDelivery(0x01)
            .withReplaceIfPresentFlag(smpp::constants::null_settings::NULL_INT8)
            .withDataCoding(smpp::constants::null_settings::NULL_INT8)
            .withSmDefaultMsgId(smpp::constants::null_settings::NULL_INT8)
            .withShortMessage("TEST_SM")
            .withOptionalParameters(
                {smpp::Tlv{smpp::constants::TAG_BILLING_IDENTIFICATION, "test_billing_id"}})};

    THEN("they should not be equal") { REQUIRE_FALSE(pdu1.equals(pdu2)); }
  }

  GIVEN("Two equal submit sm PDUs with one optional TLV parameter") {
    smpp::SubmitSm pdu1{
        smpp::builder::SubmitSmBuilder()
            .withSequenceNumber(378019)
            .withServiceType("A")
            .withSourceAddrTon(0x03)
            .withSourceAddrNpi(0x01)
            .withSourceAddr("B")
            .withDestAddrTon(0x03)
            .withDestAddrNpi(0x01)
            .withDestinationAddr("C")
            .withEsmClass(smpp::constants::null_settings::NULL_INT8)
            .withProtocolId(smpp::constants::null_settings::NULL_INT8)
            .withPriorityFlag(smpp::constants::null_settings::NULL_INT8)
            .withScheduleDeliveryTime(smpp::constants::null_settings::NULL_C_OCTET_STRING)
            .withValidityPeriod("D")
            .withRegisteredDelivery(0x01)
            .withReplaceIfPresentFlag(smpp::constants::null_settings::NULL_INT8)
            .withDataCoding(smpp::constants::null_settings::NULL_INT8)
            .withSmDefaultMsgId(smpp::constants::null_settings::NULL_INT8)
            .withShortMessage("TEST_SM")
            .withOptionalParameters(
                {smpp::Tlv{smpp::constants::TAG_BILLING_IDENTIFICATION, "test_billing_id"}})};

    smpp::SubmitSm pdu2{
        smpp::builder::SubmitSmBuilder()
            .withSequenceNumber(378019)
            .withServiceType("A")
            .withSourceAddrTon(0x03)
            .withSourceAddrNpi(0x01)
            .withSourceAddr("B")
            .withDestAddrTon(0x03)
            .withDestAddrNpi(0x01)
            .withDestinationAddr("C")
            .withEsmClass(smpp::constants::null_settings::NULL_INT8)
            .withProtocolId(smpp::constants::null_settings::NULL_INT8)
            .withPriorityFlag(smpp::constants::null_settings::NULL_INT8)
            .withScheduleDeliveryTime(smpp::constants::null_settings::NULL_C_OCTET_STRING)
            .withValidityPeriod("D")
            .withRegisteredDelivery(0x01)
            .withReplaceIfPresentFlag(smpp::constants::null_settings::NULL_INT8)
            .withDataCoding(smpp::constants::null_settings::NULL_INT8)
            .withSmDefaultMsgId(smpp::constants::null_settings::NULL_INT8)
            .withShortMessage("TEST_SM")
            .withOptionalParameters(
                {smpp::Tlv{smpp::constants::TAG_BILLING_IDENTIFICATION, "test_billing_id"}})};

    THEN("they should be equal") { REQUIRE(pdu1.equals(pdu2)); }
  }

  GIVEN("Two almost equal bind pdus") {
    smpp::BindTransmitter bindTransmitterPdu1{
        smpp::builder::BindBuilder()
            .withSequenceNumber(1)
            .withSystemId("SMPP3TEST")
            .withPassword("secret08")
            .withSystemType("SUBMIT1")
            .withInterfaceVersion(0x50)
            .withAddrTon(0x01)
            .withAddrNpi(0x01)
            .withAddressRange(smpp::constants::null_settings::NULL_C_OCTET_STRING)};

    smpp::BindTransmitter bindTransmitterPdu2{
        smpp::builder::BindBuilder()
            .withSequenceNumber(1)
            .withSystemId("SMPP4TEST")
            .withPassword("secret08")
            .withSystemType("SUBMIT1")
            .withInterfaceVersion(0x50)
            .withAddrTon(0x01)
            .withAddrNpi(0x01)
            .withAddressRange(smpp::constants::null_settings::NULL_C_OCTET_STRING)};

    THEN("they should not be equal") {
      REQUIRE_FALSE(bindTransmitterPdu1.equals(bindTransmitterPdu2));
    }
  }
}
