#ifndef AMQP_HeartbeatFrameTest_INCLUDED
#define AMQP_HeartbeatFrameTest_INCLUDED

#include "CppUnit/TestCase.h"

class HeartbeatFrameTest : public CppUnit::TestCase {
public:
  HeartbeatFrameTest(const std::string &name);
  ~HeartbeatFrameTest();

  void testFormat();

  void setUp();
  void tearDown();

  static CppUnit::Test *suite();

protected:
private:
};

#endif // AMQP_HeartbeatFrameTest_INCLUDED
