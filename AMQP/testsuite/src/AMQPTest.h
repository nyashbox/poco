#ifndef AMQPTest_INCLUDED
#define AMQPTest_INCLUDED


#include "CppUnit/TestCase.h"


class AMQPTest : public CppUnit::TestCase 
{
public:
	AMQPTest(const std::string &name);
	~AMQPTest();

	void testStub();

	void setUp();
	void tearDown();

	static CppUnit::Test *suite();

protected:
private:
};


#endif // AMQPTest_INCLUDED
