#include "Poco/AMQP/Frames/MarshalledFrame.h"
#include "Poco/AMQP/Types/Integers.h"
#include "Poco/AMQP/Types/Strings.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "MarshalledFrameTest.h"
#include <cstring>


const Poco::AMQP::Octet marshalledFrameWithType[] = 
{
	0xAA, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00
};
const Poco::AMQP::Octet marshalledFrameType = 0xAA;


const Poco::AMQP::Octet marshalledFrameWithChannel[] = 
{
	0x00, 0xAA, 0xBB, 0x00,
    0x00, 0x00, 0x00, 0x00
};
const Poco::AMQP::Short marshalledFrameChannel = 0xAABB;


const Poco::AMQP::Octet marshalledFrameWithSize[] = 
{
	0x00, 0x00, 0x00, 0xAA,
    0xBB, 0xCC, 0xDD, 0x00
};
const Poco::AMQP::Long marshalledFrameSize = 0xAABBCCDD;


MarshalledFrameTest::MarshalledFrameTest(const std::string &name)
    : CppUnit::TestCase(name) 
{
}


MarshalledFrameTest::~MarshalledFrameTest() 
{
}


void MarshalledFrameTest::testSetChannel(void) 
{
	Poco::AMQP::Octet *framePtr = const_cast<Poco::AMQP::Octet*>(_frame.getBuffer().begin());
	Poco::Buffer<Poco::AMQP::Octet> expectedFrame { marshalledFrameWithChannel, 8 };

	std::memset(framePtr, 0x00, 8);

	_frame.setChannel(marshalledFrameChannel);

	assertTrue(_frame.getBuffer() == expectedFrame);
};


void MarshalledFrameTest::testSetType(void) 
{
	Poco::AMQP::Octet *framePtr = const_cast<Poco::AMQP::Octet*>(_frame.getBuffer().begin());
	Poco::Buffer<Poco::AMQP::Octet> expectedFrame { marshalledFrameWithType, 8 };

	std::memset(framePtr, 0x00, 8);

	_frame.setType(marshalledFrameType);

	assertTrue(_frame.getBuffer() == expectedFrame);
};


void MarshalledFrameTest::testSetSize(void) 
{
	Poco::AMQP::Octet *framePtr = const_cast<Poco::AMQP::Octet*>(_frame.getBuffer().begin());
	Poco::Buffer<Poco::AMQP::Octet> expectedFrame { marshalledFrameWithSize, 8 };

	std::memset(framePtr, 0x00, 8);

	_frame.setSize(marshalledFrameSize);

	assertTrue(_frame.getBuffer() == expectedFrame);
};


void MarshalledFrameTest::testGetChannel(void) 
{
	Poco::AMQP::Octet *framePtr = const_cast<Poco::AMQP::Octet*>(_frame.getBuffer().begin());

	std::memcpy(framePtr, marshalledFrameWithChannel, 8);

	assertTrue(_frame.getChannel() == marshalledFrameChannel);
};


void MarshalledFrameTest::testGetType(void)
{
	Poco::AMQP::Octet *framePtr = const_cast<Poco::AMQP::Octet*>(_frame.getBuffer().begin());

	std::memcpy(framePtr, marshalledFrameWithType, 8);

	assertTrue(_frame.getType() == marshalledFrameType);
}


void MarshalledFrameTest::testGetSize(void)
{
	Poco::AMQP::Octet *framePtr = const_cast<Poco::AMQP::Octet*>(_frame.getBuffer().begin());

	std::memcpy(framePtr, marshalledFrameWithSize, 8);

	assertTrue(_frame.getSize() == marshalledFrameSize);
}


void MarshalledFrameTest::setUp() 
{
}


void MarshalledFrameTest::tearDown() 
{
}


void MarshalledFrameTest::testParameterPack(void)
{
	const Poco::AMQP::Octet frame[] = 
	{
		//
		//	header
		//
		0x03,                   // type:      body frame
		0x00, 0x01,             // channel:   1
		0x00, 0x00, 0x00, 0x0F, // size:      15 bytes
		// 
		//	payload start
		//
		0x01,					// AMQP::Octet
		0x00, 0x01,				// AMQP::Short 
		0x00, 0x00,	0x00, 0x01, // AMQP::Long 
		
		0x00, 0x00,	0x00, 0x00, // AMQP::LongLong 
		0x00, 0x00,	0x00, 0x01,
		//
		//	payload end
		//
		0xCE                    // frame end: 0xCE
	};
	Poco::Buffer<Poco::AMQP::Octet> expectedFrame{frame, sizeof(frame)};

	Poco::AMQP::MarshalledFrame actualFrame
	{
		// header
		Poco::AMQP::Octet	(0x03),
		Poco::AMQP::Short	(0x01),
		// payload
		Poco::AMQP::Octet	(0x01),
		Poco::AMQP::Short	(0x01),
		Poco::AMQP::Long	(0x01),
		Poco::AMQP::LongLong(0x01),
	};

	assertTrue(actualFrame.getBuffer() == expectedFrame);
}


CppUnit::Test *MarshalledFrameTest::suite() 
{
	CppUnit::TestSuite *pSuite = new CppUnit::TestSuite("MarshalledFrameTest");

	CppUnit_addTest(pSuite, MarshalledFrameTest, testSetChannel);
	CppUnit_addTest(pSuite, MarshalledFrameTest, testSetType);
	CppUnit_addTest(pSuite, MarshalledFrameTest, testSetSize);

	CppUnit_addTest(pSuite, MarshalledFrameTest, testGetChannel);
	CppUnit_addTest(pSuite, MarshalledFrameTest, testGetType);
	CppUnit_addTest(pSuite, MarshalledFrameTest, testGetSize);

	CppUnit_addTest(pSuite, MarshalledFrameTest, testParameterPack);

	return pSuite;
}
