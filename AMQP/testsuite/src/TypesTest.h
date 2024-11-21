#ifndef TypesTest_INCLUDED
#define TypesTest_INCLUDED

#include "CppUnit/TestCase.h"

class TypesTest : public CppUnit::TestCase {
public:
  TypesTest(const std::string &name);
  ~TypesTest();

  void setUp();
  void tearDown();

  void testGetMarshalledSize();
  void testMarshalling();

  static CppUnit::Test *suite();

protected:
private:
};

#endif // TypesTest_INCLUDED
