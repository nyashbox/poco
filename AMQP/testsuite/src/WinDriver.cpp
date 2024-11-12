#include "AMQPTestSuite.h"
#include "WinTestRunner/WinTestRunner.h"

class TestDriver : public CppUnit::WinTestRunnerApp {
  void testMain() {
    CppUnit::WinTestRunner runner;
    runner.addTest(AMQPTestSuite::suite());
    runner.run();
  }
};

TestDriver theDriver;
