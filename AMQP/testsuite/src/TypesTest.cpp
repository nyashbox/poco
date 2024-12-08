#include "CppUnit/TestCaller.h"
#include "CppUnit/TestCase.h"
#include "CppUnit/TestSuite.h"
#include "Poco/AMQP/Types.h"
#include "TypesTest.h"


using Poco::AMQP::LongStr;
using Poco::AMQP::Octet;
using Poco::AMQP::ShortStr;


TypesTest::TypesTest(const std::string &name) : 
	CppUnit::TestCase(name) 
{
}


TypesTest::~TypesTest() 
{
}


void TypesTest::testShortStr() {
	const size_t marshalledSize = 5;
	const Octet marshalledString[] =
	{
		0x04, 0x41, 0x41, 0x41, 0x41
	};

	Poco::Buffer<Octet> strbuf { marshalledString, marshalledSize };

	ShortStr str{"AAAA"};

	assertEquals(str.getMarshalledSize(), marshalledSize);
	assertTrue(strbuf == str.getBuffer());
};


void TypesTest::testLongStr()
{
	const size_t marshalledSize = 8;
	const Octet marshalledString[] =
	{
		0x00, 0x00, 0x00, 0x04,
		0x41, 0x41, 0x41, 0x41
	};

	Poco::Buffer<Octet> strbuf { marshalledString, marshalledSize };

	LongStr str{"AAAA"};

	assertEquals(str.getMarshalledSize(), marshalledSize);
	assertTrue(strbuf == str.getBuffer());
};


void TypesTest::setUp() 
{
};


void TypesTest::tearDown() 
{
};


CppUnit::Test *TypesTest::suite() 
{
	CppUnit::TestSuite *pSuite = new CppUnit::TestSuite("TypesTest");

	CppUnit_addTest(pSuite, TypesTest, testShortStr);
	CppUnit_addTest(pSuite, TypesTest, testLongStr);

	return pSuite;
};
