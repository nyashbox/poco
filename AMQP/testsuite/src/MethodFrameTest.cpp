#include "Poco/AMQP/Frames/MethodFrame.h"
#include "Poco/AMQP/Types/Strings.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "MethodFrameTest.h"
#include <string>


using Poco::AMQP::Octet;
using Poco::AMQP::MethodFrame;


MethodFrameTest::MethodFrameTest(const std::string &name)
	: CppUnit::TestCase(name)
{
}


MethodFrameTest::~MethodFrameTest()
{
}


void MethodFrameTest::testFormat()
{
	const Octet frame[] = 
	{
		//
		//	HEADER
		//
		0x01,                   // type:      method frame
		0x00, 0x00,             // channel:   0 
		0x00, 0x00, 0x00, 0x14, // size:      20 bytes
		//
		//	PAYLOAD
		//
		0x00, 0xFF,             // class id:  0x00FF (AMQP::Short)
		0x00, 0xFF,             // method id: 0x00FF (AMQP::Short)

		0x03, 0x41, 0x41, 0x41, // arg1: 'AAA' (AMQP::ShortStr)
		0x00, 0x00, 0x00, 0xFF, // arg2: '255' (AMQP::Long)
		
		0x00, 0x00, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0xFF, // arg3: '255' (AMQP::LongLong) 
		//
		//	PAYLOAD END
		//
		0xCE					// frame end: 0xCE
	};
	Poco::Buffer<Octet> expectedFrame { frame, sizeof(frame) };

	MethodFrame actualFrame { 
		Poco::AMQP::Short(0x00FF),	// class id
		Poco::AMQP::Short(0x00FF),	// method id

		Poco::AMQP::ShortStr("AAA"), // arg1
		Poco::AMQP::Long(255),		 // arg2
		Poco::AMQP::LongLong(255),	 // arg3

	};

	assertTrue(actualFrame.getBuffer() == expectedFrame);
}


void MethodFrameTest::setUp()
{
}


void MethodFrameTest::tearDown()
{
}


CppUnit::Test *MethodFrameTest::suite()
{
	CppUnit::TestSuite *pSuite = new CppUnit::TestSuite("MethodFrameTest");

	CppUnit_addTest(pSuite, MethodFrameTest, testFormat);

	return pSuite;
}
