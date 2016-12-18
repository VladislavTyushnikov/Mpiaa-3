#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\ÃœË¿¿ 3\Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ÃœË¿¿3ﬁÌËÚ“ÂÒÚ˚
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		static hash_table table;
		
		TEST_CLASS_INITIALIZE(init_class)
		{	
			table.add_elem(human("Teador", "Ruzveld", 27, "Nov", 1900));
			table.add_elem(human("Iosiv", "Stalin", 27, "Nov", 1900));

		}

		
		TEST_METHOD(Test1)
		{
			bool isEqual = table.find_elem("Ruzveldia", 116) == human("", "", 0, "", 0);
			Assert::AreEqual(isEqual, true);			
		}

		TEST_METHOD(Test2)
		{
			bool isEqual = table.find_elem("Ruzveld", 116) == human("Teador", "Ruzveld", 27, "Nov", 1900);
			Assert::AreEqual(isEqual, true);
		}
		TEST_METHOD(Test3)
		{
			bool isEqual = table.find_elem("Stalin", 116) == human("Iosiv", "Stalin", 27, "Nov", 1900);
			Assert::AreEqual(isEqual, true);
		}
		TEST_METHOD(Test4)
		{
			bool isEqual = table.find_elem("stalin", 116) == human("", "", 0, "", 0);
			Assert::AreEqual(isEqual, true);
		}
		TEST_METHOD(Test5)
		{
			bool isEqual = table.find_elem("", -2) == human("", "", 0, "", 0);
			Assert::AreEqual(isEqual, true);
		}

	};
	hash_table UnitTest1::table;
}