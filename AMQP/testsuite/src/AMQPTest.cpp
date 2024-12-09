#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "AMQPTest.h"


AMQPTest::AMQPTest(const std::string &name) : 
	CppUnit::TestCase(name) 
{
}


AMQPTest::~AMQPTest() 
{
}


void AMQPTest::testStub() 
{
}


void AMQPTest::setUp() 
{
}


void AMQPTest::tearDown() 
{
}


CppUnit::Test *AMQPTest::suite()
{
	CppUnit::TestSuite *pSuite = new CppUnit::TestSuite("AMQPTest");

	CppUnit_addTest(pSuite, AMQPTest, testStub);

	return pSuite;
}
