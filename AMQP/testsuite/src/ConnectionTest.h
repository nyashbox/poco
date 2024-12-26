#ifndef ConnectionTest_INCLUDED
#define ConnectionTest_INCLUDED


#include "CppUnit/TestCase.h"


class ConnectionTest : public CppUnit::TestCase
{
public:
	ConnectionTest(const std::string &name);
	~ConnectionTest();

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


#endif // ConnectionTest_INCLUDED
