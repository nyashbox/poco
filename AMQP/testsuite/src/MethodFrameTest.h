#ifndef MethodFrameTest_INCLUDED
#define MethodFrameTest_INCLUDED


#include "CppUnit/TestCase.h"


class MethodFrameTest : public CppUnit::TestCase
{
public:
	MethodFrameTest(const std::string &name);
	~MethodFrameTest();

	void testFormat();

	void setUp();
	void tearDown();

	static CppUnit::Test *suite();

protected:
private:
};


#endif // MethodFrameTest_INCLUDED
