#include "Poco/AMQP/Frames/MarshalledFrame.h"

#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "MarshalledFrameTest.h"

#include <cstring>

const uint8_t marshalledFrameWithType[] = {0xFF, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0x00};
const uint8_t marshalledFrameType = 0xFF;

const uint8_t marshalledFrameWithChannel[] = {0x00, 0xFF, 0xFF, 0x00,
                                              0x00, 0x00, 0x00, 0x00};
const uint16_t marshalledFrameChannel = 0xFFFF;

const uint8_t marshalledFrameWithSize[] = {0x00, 0x00, 0x00, 0xFF,
                                           0xFF, 0xFF, 0xFF, 0x00};
const uint32_t marshalledFrameSize = 0xFFFFFFFF;

MarshalledFrameTest::MarshalledFrameTest(const std::string &name)
    : CppUnit::TestCase(name) {}

MarshalledFrameTest::~MarshalledFrameTest() {}

void MarshalledFrameTest::testSetChannel(void) {
  std::memset(_frame.getData(), 0x00, 8);

  _frame.setChannel(marshalledFrameChannel);

  assertEquals(std::memcmp(_frame.getData(), marshalledFrameWithChannel, 8), 0);
};

void MarshalledFrameTest::testSetType(void) {
  std::memset(_frame.getData(), 0x00, 8);

  _frame.setType(marshalledFrameType);

  assertEquals(std::memcmp(_frame.getData(), marshalledFrameWithType, 8), 0);
};

void MarshalledFrameTest::testSetSize(void) {
  std::memset(_frame.getData(), 0x00, 8);

  _frame.setSize(marshalledFrameSize);

  assertEquals(std::memcmp(_frame.getData(), marshalledFrameWithSize, 8), 0);
};

void MarshalledFrameTest::testGetChannel(void) {
  std::memcpy(_frame.getData(), marshalledFrameWithChannel, 8);

  uint16_t channel = _frame.getChannel();

  assertEquals(
      std::memcmp(&marshalledFrameWithChannel[1], &channel, sizeof(channel)),
      0);
};

void MarshalledFrameTest::testGetType(void) {
  std::memcpy(_frame.getData(), marshalledFrameWithType, 8);

  uint8_t type = _frame.getType();

  assertEquals(std::memcmp(&marshalledFrameWithType[0], &type, sizeof(type)),
               0);
};

void MarshalledFrameTest::testGetSize(void) {
  std::memcpy(_frame.getData(), marshalledFrameWithSize, 8);

  uint32_t size = _frame.getSize();

  assertEquals(std::memcmp(&marshalledFrameWithSize[3], &size, sizeof(size)),
               0);
};

void MarshalledFrameTest::setUp() {};
void MarshalledFrameTest::tearDown() {};

void MarshalledFrameTest::setUpSuite() {};
void MarshalledFrameTest::tearDownSuite() {};

CppUnit::Test *MarshalledFrameTest::suite() {
  CppUnit::TestSuite *pSuite = new CppUnit::TestSuite("MarshalledFrameTest");

  CppUnit_addTest(pSuite, MarshalledFrameTest, testSetChannel);
  CppUnit_addTest(pSuite, MarshalledFrameTest, testSetType);
  CppUnit_addTest(pSuite, MarshalledFrameTest, testSetSize);

  CppUnit_addTest(pSuite, MarshalledFrameTest, testGetChannel);
  CppUnit_addTest(pSuite, MarshalledFrameTest, testGetType);
  CppUnit_addTest(pSuite, MarshalledFrameTest, testGetSize);

  return pSuite;
}
