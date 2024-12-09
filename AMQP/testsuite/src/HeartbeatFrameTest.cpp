#include "Poco/AMQP/Frames/HeartbeatFrame.h"
#include "Poco/AMQP/Frames/MarshalledFrame.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "HeartbeatFrameTest.h"
#include <cstring>


using Poco::AMQP::HeartbeatFrame;
using Poco::AMQP::MarshalledFrame;
using Poco::AMQP::Octet;


HeartbeatFrameTest::HeartbeatFrameTest(const std::string &name)
    : CppUnit::TestCase(name) 
{
}


HeartbeatFrameTest::~HeartbeatFrameTest() 
{
}


void HeartbeatFrameTest::testFormat() 
{
	const Octet testFrame[] = 
	{
		0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCE
	};
	Poco::Buffer<Octet> expectedFrame { testFrame, sizeof(testFrame) };

	MarshalledFrame marshalledFrame = HeartbeatFrame().marshall();

	assertTrue(marshalledFrame.getBuffer() == expectedFrame);
}


void HeartbeatFrameTest::setUp() 
{
}


void HeartbeatFrameTest::tearDown() 
{
}


CppUnit::Test *HeartbeatFrameTest::suite()
{
	CppUnit::TestSuite *pSuite = new CppUnit::TestSuite("HeartbeatFrameTest");

	CppUnit_addTest(pSuite, HeartbeatFrameTest, testFormat);

	return pSuite;
}
