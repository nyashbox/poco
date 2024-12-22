#ifndef FrameIOTest_INCLUDED
#define FrameIOTest_INCLUDED


#include "CppUnit/TestCase.h"


class FrameIOTest : public CppUnit::TestCase
{
public:
	FrameIOTest(const std::string &name);
	~FrameIOTest();

	void testConnect();
	void testNegotiate();

	void testWrite();
	void testRead();

	void setUp();
	void tearDown();

	static CppUnit::Test *suite();

protected:
private:
};


#endif // FrameIOTest_INCLUDED
