#include "AMQPTestSuite.h"
#include "AMQPTest.h"

CppUnit::Test *AMQPTestSuite::suite() {
  CppUnit::TestSuite *pSuite = new CppUnit::TestSuite("AMQPTestSuite");

  pSuite->addTest(AMQPTest::suite());

  return pSuite;
}
