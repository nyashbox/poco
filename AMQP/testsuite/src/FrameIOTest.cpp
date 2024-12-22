#include "Poco/AMQP/Networking/FrameIO.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "FrameIOTest.h"
#include "Poco/AMQP/Frames/HeartbeatFrame.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/StreamSocket.h"


const Poco::AMQP::Octet heartbeatFrame[] = 
{
	0x08,                   // type:      heartbeat frame 
	0x00, 0x00,             // channel:   0
	0x00, 0x00, 0x00, 0x00, // size:      0 bytes
	0xCE                    // frame end: 0xCE
};


FrameIOTest::FrameIOTest(const std::string &name)
	: CppUnit::TestCase(name)
{
}


FrameIOTest::~FrameIOTest() 
{
}


void FrameIOTest::testConnect()
{
	Poco::Net::ServerSocket server(55555);

	// correct connection MUST NOT throw
	try {
		Poco::AMQP::FrameIO io("127.0.0.1", 55555);
	}
	catch (...) 
	{
		assertTrue(false);
	}

	// incorrect connection MUST throw
	try {
		Poco::AMQP::FrameIO io("127.0.0.1", 1);

		assertTrue(false);
	}
	catch (...)
	{
	}

	server.close();
}


void FrameIOTest::testNegotiate()
{
	const char protocolHeader[] = {
		'A', 'M', 'Q', 'P', 0, 0, 9, 1
	};

	Poco::Buffer<char> expectedProtocolHeader 
	{
		protocolHeader, sizeof(protocolHeader) 
	};

	Poco::Net::ServerSocket socket(55555);
	Poco::AMQP::FrameIO io("127.0.0.1", 55555);

	Poco::Net::StreamSocket client = socket.acceptConnection();

	// perform connection negotiation
	io.negotiate();

	Poco::Buffer<char> actualProtocolHeader{8};
	client.receiveBytes(actualProtocolHeader);

	assertTrue(expectedProtocolHeader == actualProtocolHeader);

	// close all connections
	socket.close();
	io.disconnect();
}


void FrameIOTest::testWrite()
{
	Poco::Buffer<Poco::AMQP::Octet> expectedFrame 
	{
		heartbeatFrame, sizeof(heartbeatFrame) 
	};

	Poco::Buffer<Poco::AMQP::Octet> actualFrame
	{
		sizeof(heartbeatFrame) 
	};

	Poco::Net::ServerSocket server{55555};

	Poco::AMQP::FrameIO io{"127.0.0.1", 55555};
	Poco::Net::StreamSocket client = server.acceptConnection();

	io.write(Poco::AMQP::HeartbeatFrame());
	assertTrue(client.available() == sizeof(heartbeatFrame));

	client.receiveBytes(actualFrame.begin(), client.available());
	assertTrue(actualFrame == expectedFrame);

	// close all connections
	io.disconnect();
	server.close();
}


void FrameIOTest::testRead()
{
	Poco::Buffer<Poco::AMQP::Octet> expectedFrame 
	{ 
		heartbeatFrame, sizeof(heartbeatFrame) 
	};

	Poco::Net::ServerSocket server{55555};

	Poco::AMQP::FrameIO io{"127.0.0.1", 55555};
	Poco::Net::StreamSocket client = server.acceptConnection();

	client.sendBytes(heartbeatFrame, sizeof(heartbeatFrame));

	Poco::Buffer<Poco::AMQP::Octet> actualFrame = io.read();
	assertTrue(actualFrame == expectedFrame);

	// close all connections
	io.disconnect();
	server.close();
}


void FrameIOTest::setUp()
{
}


void FrameIOTest::tearDown()
{
}


CppUnit::Test *FrameIOTest::suite()
{
	CppUnit::TestSuite *pSuite = new CppUnit::TestSuite("FrameIOTest");

	CppUnit_addTest(pSuite, FrameIOTest, testConnect);
	CppUnit_addTest(pSuite, FrameIOTest, testNegotiate);

	CppUnit_addTest(pSuite, FrameIOTest, testWrite);
	CppUnit_addTest(pSuite, FrameIOTest, testRead);

	return pSuite;
}
