#include "AMQPTestSuite.h"
#include "BodyFrameTest.h"
#include "HeartbeatFrameTest.h"
#include "MarshalledFrameTest.h"
#include "TypesTest.h"


CppUnit::Test *AMQPTestSuite::suite() 
{
	CppUnit::TestSuite *pSuite = new CppUnit::TestSuite("AMQPTestSuite");

	// frames tests
	pSuite->addTest(MarshalledFrameTest::suite());
	pSuite->addTest(BodyFrameTest::suite());
	pSuite->addTest(HeartbeatFrameTest::suite());

	// types tests
	pSuite->addTest(TypesTest::suite());

	return pSuite;
}
