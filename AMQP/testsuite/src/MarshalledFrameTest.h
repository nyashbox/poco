#ifndef MarshalledFrame_INCLUDED
#define MarshalledFrame_INCLUDED

#include "CppUnit/TestCase.h"

#include "Poco/AMQP/Frames/MarshalledFrame.h"

class MarshalledFrameTest : public CppUnit::TestCase {
public:
  MarshalledFrameTest(const std::string &name);
  ~MarshalledFrameTest();

  void testSetChannel(void);
  void testSetType(void);
  void testSetSize(void);

  void testGetChannel(void);
  void testGetType(void);
  void testGetSize(void);

  void setUp();
  void tearDown();

  static void setUpSuite();
  static void tearDownSuite();

  static CppUnit::Test *suite();

protected:
private:
  Poco::AMQP::MarshalledFrame _frame;
};

#endif // MarshalledFrame_INCLUDED
