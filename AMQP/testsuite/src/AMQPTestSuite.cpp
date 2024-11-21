#include "AMQPTestSuite.h"
#include "AMQPTest.h"
#include "HeartbeatFrameTest.h"
#include "MarshalledFrameTest.h"
#include "TypesTest.h"

CppUnit::Test *AMQPTestSuite::suite() {
  CppUnit::TestSuite *pSuite = new CppUnit::TestSuite("AMQPTestSuite");

  pSuite->addTest(AMQPTest::suite());
  pSuite->addTest(TypesTest::suite());

  pSuite->addTest(MarshalledFrameTest::suite());
  pSuite->addTest(HeartbeatFrameTest::suite());

  return pSuite;
}
