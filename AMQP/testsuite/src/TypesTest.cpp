#include "CppUnit/TestCaller.h"
#include "CppUnit/TestCase.h"
#include "CppUnit/TestSuite.h"
#include "Poco/AMQP/Types.h"
#include "TypesTest.h"


using Poco::AMQP::Octet;
using Poco::AMQP::Short;
using Poco::AMQP::Long;
using Poco::AMQP::LongLong;

using Poco::AMQP::ShortStr;
using Poco::AMQP::LongStr;


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

	assertTrue(strbuf == str.getBuffer());
};


void TypesTest::testFieldTable()
{
	// test table
	const Octet fieldTable[] = 
	{
		0x01, '1', 's', 0x01, 'A',
		0x01, '2', 'S', 0x00, 0x00, 0x00, 0x01, 'A',
		0x01, '3', 'B', 0xFF,
		0x01, '4', 'u', 0xFF, 0xFF,
		0x01, '5', 'i', 0xFF, 0xFF, 0xFF, 0xFF,
		0x01, '6', 'l', 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	};

	Poco::Buffer<Octet> fieldTableBuffer{fieldTable, sizeof(fieldTable)};
	Poco::AMQP::FieldTable table;

	// test inserting strings
	table.insert({"1"}, ShortStr("A"));
	table.insert({"2"},  LongStr("A"));

	// test inserting integers 
	table.insert({"3"},    (Poco::AMQP::Octet)0x00000000000000FF);
	table.insert({"4"},    (Poco::AMQP::Short)0x000000000000FFFF);
	table.insert({"5"}, 	(Poco::AMQP::Long)0x00000000FFFFFFFF);
	table.insert({"6"}, (Poco::AMQP::LongLong)0xFFFFFFFFFFFFFFFF);

	assertTrue(fieldTableBuffer == table.getBuffer());
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
	CppUnit_addTest(pSuite, TypesTest, testFieldTable);

	return pSuite;
};
