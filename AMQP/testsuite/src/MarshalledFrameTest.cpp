#include "Poco/AMQP/Frames/MarshalledFrame.h"

#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "MarshalledFrameTest.h"

#include <cstring>

const Poco::AMQP::Octet marshalledFrameWithType[] = {0xAA, 0x00, 0x00, 0x00,
                                                     0x00, 0x00, 0x00, 0x00};
const Poco::AMQP::Octet marshalledFrameType = 0xAA;

const Poco::AMQP::Octet marshalledFrameWithChannel[] = {0x00, 0xAA, 0xBB, 0x00,
                                                        0x00, 0x00, 0x00, 0x00};
const Poco::AMQP::Short marshalledFrameChannel = 0xAABB;

const Poco::AMQP::Octet marshalledFrameWithSize[] = {0x00, 0x00, 0x00, 0xAA,
                                                     0xBB, 0xCC, 0xDD, 0x00};
const Poco::AMQP::Long marshalledFrameSize = 0xAABBCCDD;

MarshalledFrameTest::MarshalledFrameTest(const std::string &name)
    : CppUnit::TestCase(name) {}

MarshalledFrameTest::~MarshalledFrameTest() {}

void MarshalledFrameTest::testSetChannel(void) {
  std::memset(_frame.begin(), 0x00, 8);

  _frame.setChannel(marshalledFrameChannel);

  assertEquals(std::memcmp(_frame.begin(), marshalledFrameWithChannel, 8), 0);
};

void MarshalledFrameTest::testSetType(void) {
  std::memset(_frame.begin(), 0x00, 8);

  _frame.setType(marshalledFrameType);

  assertEquals(std::memcmp(_frame.begin(), marshalledFrameWithType, 8), 0);
};

void MarshalledFrameTest::testSetSize(void) {
  std::memset(_frame.begin(), 0x00, 8);

  _frame.setSize(marshalledFrameSize);

  assertEquals(std::memcmp(_frame.begin(), marshalledFrameWithSize, 8), 0);
};

void MarshalledFrameTest::testGetChannel(void) {
  std::memcpy(_frame.begin(), marshalledFrameWithChannel, 8);

  assertTrue(_frame.getChannel() == marshalledFrameChannel);
};

void MarshalledFrameTest::testGetType(void) {
  std::memcpy(_frame.begin(), marshalledFrameWithType, 8);

  assertTrue(_frame.getType() == marshalledFrameType);
};

void MarshalledFrameTest::testGetSize(void) {
  std::memcpy(_frame.begin(), marshalledFrameWithSize, 8);

  assertTrue(_frame.getSize() == marshalledFrameSize);
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
