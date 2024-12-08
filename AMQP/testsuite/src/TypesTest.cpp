#include "CppUnit/TestCaller.h"
#include "CppUnit/TestCase.h"
#include "CppUnit/TestSuite.h"
#include "Poco/AMQP/Types.h"
#include "TypesTest.h"


using Poco::AMQP::LongStr;
using Poco::AMQP::Octet;
using Poco::AMQP::ShortStr;


const Octet longStringExpectedLength = 8;
const Octet shortStringExpectedLength = 5;


TypesTest::TypesTest(const std::string &name) : 
	CppUnit::TestCase(name) 
{
}


TypesTest::~TypesTest() 
{
}


void TypesTest::testGetMarshalledSize() 
{
	LongStr longString{"AAAA"};
	ShortStr shortString{"AAAA"};

	assertEquals(longString.getMarshalledSize(), longStringExpectedLength);
	assertEquals(shortString.getMarshalledSize(), shortStringExpectedLength);
};


void TypesTest::testMarshalling() 
{
	const Octet marshalledShortString[] = {0x04, 0x41, 0x41, 0x41, 0x41};
	const Octet marshalledLongString[] = {0x00, 0x00, 0x00, 0x04,
										0x41, 0x41, 0x41, 0x41};

	LongStr longString{"AAAA"};
	ShortStr shortString{"AAAA"};

	Octet buf[longStringExpectedLength];

	longString.marshall(buf);
	assertEquals(std::memcmp(marshalledLongString, buf, longStringExpectedLength),
			   0);

	shortString.marshall(buf);
	assertEquals(
	  std::memcmp(marshalledShortString, buf, shortStringExpectedLength), 0);
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

	CppUnit_addTest(pSuite, TypesTest, testGetMarshalledSize);
	CppUnit_addTest(pSuite, TypesTest, testMarshalling);

	return pSuite;
};
