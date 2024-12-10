#include "Poco/AMQP/Frames/BodyFrame.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "BodyFrameTest.h"
#include <string>


using Poco::AMQP::Octet;


BodyFrameTest::BodyFrameTest(const std::string &name)
	: CppUnit::TestCase(name)
{
}


BodyFrameTest::~BodyFrameTest()
{
}


void BodyFrameTest::testFormat()
{
	const Octet frame[] = 
	{
		0x03,                   // type:      body frame
		0x00, 0x01,             // channel:   1
		0x00, 0x00, 0x00, 0x04, // size:      4 bytes
		0x41, 0x41, 0x41, 0x41, // payload:   'AAAA' 
		0xCE                    // frame end: 0xCE
	};
	Poco::Buffer<Octet> expectedFrame {frame, sizeof(frame)};
	const Octet str[] = { 0x41, 0x41, 0x41, 0x41 };

	Poco::AMQP::BodyFrame actualFrame { str, sizeof(str), 0x01 };

	assertTrue(actualFrame.getBuffer() == expectedFrame);
}


void BodyFrameTest::setUp()
{
}


void BodyFrameTest::tearDown()
{
}


CppUnit::Test *BodyFrameTest::suite()
{
	CppUnit::TestSuite *pSuite = new CppUnit::TestSuite("BodyFrameTest");

	CppUnit_addTest(pSuite, BodyFrameTest, testFormat);

	return pSuite;
}
