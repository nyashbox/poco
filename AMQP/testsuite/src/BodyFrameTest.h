#ifndef BodyFrameTest_INCLUDED
#define BodyFrameTest_INCLUDED


#include "CppUnit/TestCase.h"


class BodyFrameTest : public CppUnit::TestCase
{
public:
	BodyFrameTest(const std::string &name);
	~BodyFrameTest();

	void testFormat();

	void setUp();
	void tearDown();

	static CppUnit::Test *suite();

protected:
private:
};


#endif // BodyFrameTest_INCLUDED
