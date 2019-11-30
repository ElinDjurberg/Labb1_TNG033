// doctest tutorial: not mandatory to read
// https://github.com/onqtam/doctest/blob/master/doc/markdown/tutorial.md
// https://github.com/onqtam/doctest/blob/master/doc/markdown/main.md

#define DOCTEST_CONFIG_IMPLEMENT

#include <sstream>  //istringstream
#include <string>

#include "doctest.hpp"
#include "set.hpp"
#include "set.hpp"

int main(int argc, char** argv) {
	doctest::Context context(argc, argv);

	// context.setOption("success", true);    // Print all test cases even successful ones

	context.setOption("no-breaks", true);  // Don't break in the debugger when assertions fail

	// context.setOption("no-path-filenames", true);  // Use short paths

	return context.run();
}

/************************************************
 * TEST PHASE 1: constructors                   *
 *               empty                          *
 *               cardinality                    *
 ************************************************/

TEST_SUITE("Phase 1: Constructors") {

	TEST_CASE("Default Constructor") {
		const Set empty{};

		SUBCASE("Test whether empty set") {
			CHECK(empty.empty());
		}

		SUBCASE("Check set members") {
			CHECK_FALSE(empty.member(0));
		}
	}
}

TEST_CASE("Single Element Constructor") {
	const Set s1{ 999 };

	SUBCASE("Check set cardinality") {

		CHECK(s1.cardinality() == 1);
	}

	SUBCASE("Check set members") {
		CHECK(s1.member(999));
		CHECK_FALSE(s1.member(998));
	}
}

TEST_CASE("List Constructor") {
	const int list[] = { 4, 11, 9, 6 };
	const int listSize{ 4 };

	const Set s1{ list, listSize };

	SUBCASE("Check set cardinality") {
		CHECK(s1.cardinality() == listSize);
	}

	SUBCASE("Check set members") {
		CHECK(s1.member(4));
		CHECK(s1.member(11));
		CHECK(s1.member(9));
		CHECK(s1.member(6));
	}

	SUBCASE("Check set members") {
		CHECK_FALSE(s1.member(998));
	}

	SUBCASE("Check set members sorting") {
		std::ostringstream os;
		os << s1;

		CHECK(os.str() == std::string("{ 4 6 9 11 }"));
	}
}

TEST_CASE("Copy Constructor") {
	const int list[] = { 4, 11, 9 };
	const int listSize{ 3 };

	const Set s1{ list, listSize };
	const Set s2{ s1 };

	SUBCASE("Check set cardinality") {
		CHECK(s2.cardinality() == listSize);
	}

	SUBCASE("Check set members") {
		CHECK(s2.member(4));
		CHECK(s2.member(11));
		CHECK(s2.member(9));
	}

	SUBCASE("Check set members") {
		CHECK_FALSE(s2.member(10));
	}

	SUBCASE("Check set members sorting") {
		std::ostringstream os;
		os << s2;

		CHECK(os.str() == std::string("{ 4 9 11 }"));
	}
}


/************************************************
 * TEST PHASE 2: assignment                     *
 ************************************************/

TEST_SUITE("Phase 2: Assignment") {

	TEST_CASE("Assignment operator: empty set on LHS") {
		const int list[] = { 9, 11, 4 }; // s1
		const int listSize{ 3 };

		const Set s1{ list, listSize };
		Set s2{}; // tom

		SUBCASE("Check whether set is empty") {
			CHECK(s2.empty());
		}

		s2 = s1; // s2 får samma som s1

		SUBCASE("Check set cardinality") {
			CHECK(s2.cardinality() == listSize);
		}

		SUBCASE("Check set members") {
			CHECK(s1.member(4));
			CHECK(s1.member(11));
			CHECK(s1.member(9));
		}

		SUBCASE("Check LHS set members sorting") {
			std::ostringstream os;
			os << s2;

			CHECK(os.str() == std::string("{ 4 9 11 }"));
		}
	}

	TEST_CASE("Assignment operator: non-empty set on LHS") {
		const int list1[] = { 4, 11, 9 };
		const int listSize1{ 3 };

		Set s1{ list1, listSize1 };

		const int list2[] = { 4, 3, 2, 11, 9 };
		const int listSize2{ 5 };

		const Set s2{ list2, listSize2 };

		s1 = s2;

		SUBCASE("Check set cardinality") {
			CHECK(s2.cardinality() == s1.cardinality());
		}

		SUBCASE("Check set members on LHS") {
			CHECK(s1.member(3));
			CHECK(s1.member(2));
			CHECK(s1.member(4));
			CHECK(s1.member(9));
			CHECK(s1.member(11));
		}

		SUBCASE("Check set members on RHS") {
			CHECK(s2.member(3));
			CHECK(s2.member(2));
			CHECK(s2.member(4));
			CHECK(s2.member(9));
			CHECK(s2.member(11));
		}

		SUBCASE("Check LHS set members sorting") {
			std::ostringstream os;
			os << s1;

			CHECK(os.str() == std::string("{ 2 3 4 9 11 }"));
		}
	}

	TEST_CASE("Assignment operator: empty set on RHS") {
		const int list1[] = { 4, 11, 9 };
		const int listSize1{ 3 };

		Set s1{ list1, listSize1 };

		s1 = Set{};

		SUBCASE("Check empty set on LHS") {
			CHECK(s1.empty());
		}
	}
}

//TEST_SUITE("Phase 3: Set Operations") {
//
//    /************************************************
//     * TEST PHASE 3.a: operator+                    *
//     *                 S1+S2                        *
//     *                 S+int                        *
//     ************************************************/

TEST_CASE("Union: S + {x}") {
	const int list[] = { 4, 11, 9 };
	const int listSize{ 3 };

	const Set s1{ list, listSize };
	const Set s2{ 999 };

	const Set s3 = s1 + s2;

	SUBCASE("Check set cardinality") {
		CHECK(s3.cardinality() == listSize + 1);
	}

	SUBCASE("Check set members") {
		CHECK(s3.member(4));
		CHECK(s3.member(11));
		CHECK(s3.member(9));
		CHECK(s3.member(999));
	}

	SUBCASE("Check set members sorting") {
		std::ostringstream os;
		os << s3;

		CHECK(os.str() == std::string("{ 4 9 11 999 }"));
	}
}

TEST_CASE("Union: S1 + S2") {
	const int list1[] = { 1, 3, 5 };
	const int listSize1{ 3 };

	const int list2[] = { 4, 3, 2, 11, 9 };
	const int listSize2{ 5 };

	const Set s1{ list1, listSize1 };
	const Set s2{ list2, listSize2 };

	const Set s3 = s1 + s2;

	SUBCASE("Check set cardinality") {
		CHECK(s3.cardinality() == 7);
	}

	SUBCASE("Check set members") {
		CHECK(s3.member(1));
		CHECK(s3.member(2));
		CHECK(s3.member(3));
		CHECK(s3.member(4));
		CHECK(s3.member(5));
		CHECK(s3.member(9));
		CHECK(s3.member(11));
	}





	SUBCASE("Check set members sorting") {
		std::ostringstream os;
		os << s3;

		CHECK(os.str() == std::string("{ 1 2 3 4 5 9 11 }"));
	}
}

TEST_CASE("Union: {} + S") {
	const int list1[] = { 4, 3, 2, 11, 9 };
	const int listSize1{ 5 };

	const Set s1{ list1, listSize1 };
	const Set s2 = Set{} +s1;

	SUBCASE("Check set cardinality") {
		CHECK(s2.cardinality() == 5);
	}

	SUBCASE("Check set members sorting") {
		std::ostringstream os;
		os << s2;

		CHECK(os.str() == std::string("{ 2 3 4 9 11 }"));
	}
}
//No leaks


TEST_CASE("Union: S + int") {
	const int list[] = { 4, 11, 9 };
	const int listSize{ 3 };

	const Set s1{ list, listSize };

	SUBCASE("Add non-existing element") {
		const Set s2{ s1 + 999 };
		// const Set s2 = 999 + s1; //doesn't compile, so operator+ is not commutative
			//ska vi göra något åt denna?

		SUBCASE("Check set cardinality") {
			CHECK(s2.cardinality() == listSize + 1);
		}

		SUBCASE("Check set members") {
			CHECK(s2.member(4));
			CHECK(s2.member(11));
			CHECK(s2.member(9));
			CHECK(s2.member(999));
		}

		SUBCASE("Check set members sorting") {
			std::ostringstream os;
			os << s2;

			CHECK(os.str() == std::string("{ 4 9 11 999 }"));
		}
	}

	SUBCASE("Add existing element") {
		const Set s2{ s1 + 4 };

		SUBCASE("Check set cardinality") {
			CHECK(s2.cardinality() == listSize);
		}

		SUBCASE("Check set members") {
			CHECK(s2.member(4));
			CHECK(s2.member(11));
			CHECK(s2.member(9));
		}
	}
}
//No leaks

////    /************************************************
////     * TEST PHASE 3.b: operator*                    *
////     *                 S1*S2                        *
////     *                 S*int                        *
////     ************************************************/
//
TEST_CASE("Intersection: S1 * S2") {
	const int list[] = { 4, 11, 9 };
	const int listSize{ 3 };

	const Set s1{ list, listSize };

	SUBCASE("Emtpy intersection") {
		const Set s2{ 999 };
		const Set s3{ s1 * s2 };

		SUBCASE("Check set cardinality") {
			CHECK(s3.cardinality() == 0);
		}
	}

	SUBCASE("Intersection: S * {}") {
		const Set empty{};
		const Set s3 = s1 * empty;

		SUBCASE("Check set cardinality") {
			CHECK(s3.cardinality() == 0);
		}
	}




	SUBCASE("Partial intersection") {
		const int list2[] = { 5, 4, 11, 2 };
		const Set s2{ list2, 4 };
		const Set s3{ s1 * s2 };

		SUBCASE("Check s cardinality") {
			CHECK(s3.cardinality() == 2);
		}

		SUBCASE("Check set members") {
			CHECK(s3.member(4));
			CHECK(s3.member(11));
		}

		SUBCASE("Check set members sorting") {
			std::ostringstream os;
			os << s3;

			CHECK(os.str() == std::string("{ 4 11 }"));
		}
	}

	SUBCASE("Intersection of two sets with same elements") {
		const Set s2{ s1 };
		const Set s3{ s1 * s2 };

		SUBCASE("Check set cardinality") {
			CHECK(s3.cardinality() == listSize);
		}

		SUBCASE("Check set members") {
			CHECK(s3.member(4));
			CHECK(s3.member(11));
			CHECK(s3.member(9));
		}

		SUBCASE("Check set members sorting") {
			std::ostringstream os;
			os << s3;

			CHECK(os.str() == std::string("{ 4 9 11 }"));
		}
	}
}
//No leaks
////
////    /************************************************
////     * TEST PHASE 3.c: operator-                    *
////     *                 S1-S2                        *
////     *                 S-int                        *
////     ************************************************/
//
TEST_CASE("Difference: S1 - S2") {
	const int list[] = { 4, 11, 6, 9 };
	const int listSize{ 3 };

	const int list2[] = { 1, 7, 11, 5, 9 };
	const int listSize2{ 5 };

	const Set s1{ list, listSize };
	const Set s2{ list2, listSize2 };

	const Set s3{ s1 - s2 };

	SUBCASE("Check set cardinality") {
		CHECK(s3.cardinality() == 2);
	}

	SUBCASE("Check set members") {
		CHECK(s3.member(4));
		CHECK(s3.member(6));
	}

	SUBCASE("Check all set members") {
		std::ostringstream os;
		os << s3;

		CHECK(os.str() == std::string("{ 4 6 }"));
	}
}

TEST_CASE("Difference: S1 - S1") {
	const int list[] = { 4, 11, 6, 9 };
	const int listSize{ 4 };

	const Set s1{ list, listSize };

	const Set s2{ s1 - s1 };

	SUBCASE("Check whether set is empty") {
		CHECK(s2.empty());
	}
}

TEST_CASE("Difference: S1 - {}") {
	const int list[] = { 4, 11, 6, 9 };
	const int listSize{ 4 };

	const Set s1{ list, listSize };
	const Set s2{ s1 - Set{} };

	SUBCASE("Check set cardinality") {
		CHECK(s2.cardinality() == 4);
	}

	SUBCASE("Check set members sorting") {
		std::ostringstream os;
		os << s2;

		CHECK(os.str() == std::string("{ 4 6 9 11 }"));
	}
}

TEST_CASE("Difference: S - int") {
	const int list[] = { 4, 11, 9 };
	const int listSize{ 3 };

	const Set s1{ list, listSize };

	SUBCASE("Remove existing member") {
		const Set s2{ s1 - 11 };

		SUBCASE("Check set cardinality") {
			CHECK(s2.cardinality() == 2);
		}

		SUBCASE("Check set members") {
			CHECK(s2.member(4));
			CHECK(s2.member(9));
		}
	}

	SUBCASE("Remove non-existing member") {
		const Set s2{ s1 - 42 };

		SUBCASE("Check set cardinality") {
			CHECK(s2.cardinality() == 3);
		}

		SUBCASE("Check set members") {
			CHECK(s2.member(4));
			CHECK(s2.member(11));
			CHECK(s2.member(9));
		}
	}
}
//No leaks
//
///************************************************
// * TEST PHASE 4: Comparison operators           *
// *                 S1 == S2                     *
// *                 S1 != S2                     *
// *                 S1 < S2                      *
// *                 S1 <= S2                     *
// ************************************************/
//
TEST_SUITE("Phase 4: Relational Operators") {

	TEST_CASE("Equality: S1 == S2") {
		const int list[] = { 4, 11, 9 };
		const int listSize{ 3 };

		const Set s1{ list, listSize };

		SUBCASE("Identical sets") {
			const Set s2{ s1 };

			CHECK(s1 == s2);
			CHECK(s2 == s2);
		}

		SUBCASE("Non-identical sets (same cardinality)") {
			const int list2[] = { 4, 12, 10 };
			const int listSize2{ 3 };
			const Set s2{ list2, listSize2 };

			CHECK_FALSE(s1 == s2);
			CHECK_FALSE(s2 == s1);
		}

		SUBCASE("Non-identical sets (different cardinality)") {
			const int list2[] = { 4, 11 };
			const int listSize2{ 2 };
			const Set s2{ list2, listSize2 };

			CHECK_FALSE(s1 == s2);
			CHECK_FALSE(s2 == s1);
		}
	}

	TEST_CASE("Non-equality: S1 != S2") {
		const int list[] = { 4, 11, 9 };
		const int listSize{ 3 };

		const Set s1{ list, listSize };

		SUBCASE("Identical sets") {
			const Set s2{ s1 };

			CHECK_FALSE(s1 != s2);
			CHECK_FALSE(s2 != s1);
		}

		SUBCASE("Non-identical sets (same cardinality)") {
			const int list2[] = { 4, 12, 10 };
			const int listSize2{ 3 };
			const Set s2{ list2, listSize2 };

			CHECK(s1 != s2);
			CHECK(s2 != s1);
		}

		SUBCASE("Non-identical sets (different cardinality)") {
			const int list2[] = { 4, 11 };
			const int listSize2{ 2 };
			const Set s2{ list2, listSize2 };

			CHECK(s1 != s2);
			CHECK(s2 != s1);
		}
	}

	TEST_CASE("Proper subset (operator<)") {
		const int list[] = { 4, 11, 9 };
		const int listSize{ 3 };

		const Set s1{ list, listSize };

		SUBCASE("Identical sets") {
			const Set s2{ s1 };

			CHECK_FALSE(s1 < s2);
			CHECK_FALSE(s2 < s1);
		}

		SUBCASE("Empty set") {
			const Set empty{};

			CHECK(empty < s1);
			CHECK_FALSE(empty < empty);
			CHECK_FALSE(s1 < empty);
		}

		SUBCASE("Proper subset (single element)") {
			const Set s2{ 4 };

			CHECK(s2 < s1);
			CHECK_FALSE(s1 < s2);
		}

		SUBCASE("Proper subset (cardinality 2)") {
			const int list2[] = { 4, 11 };
			const int listSize2{ 2 };
			const Set s2{ list2, listSize2 };

			CHECK(s2 < s1);
			CHECK_FALSE(s1 < s2);
		}

		SUBCASE("Distinct sets") {
			const int list2[] = { 5, 10, 42 };
			const int listSize2{ 3 };
			const Set s2{ list2, listSize2 };

			CHECK_FALSE(s1 < s2);
			CHECK_FALSE(s2 < s1);
		}
	}

	TEST_CASE("Subset (operator<=)") {
		const int list[] = { 4, 11, 9 };
		const int listSize{ 3 };

		const Set s1{ list, listSize };

		SUBCASE("Identical sets") {
			const Set s2{ s1 };

			CHECK(s1 <= s2);
			CHECK(s2 <= s1);
		}


		SUBCASE("Empty set") {
			const Set empty{};

			CHECK(empty <= s1);//sant S1 är det vi skickar in. empty är den vi är i. Ska kolla om empty är en subklass
			CHECK(empty <= empty);//sant
			CHECK_FALSE(s1 <= empty);//falskt
		}


		SUBCASE("Subset (single element)") {
			const Set s2{ 4 };

			CHECK(s2 <= s1);
			CHECK_FALSE(s1 <= s2);
		}

		SUBCASE("Subset (cardinality 2)") {
			const int list2[] = { 4, 11 };
			const int listSize2{ 2 };
			const Set s2{ list2, listSize2 };

			CHECK(s2 <= s1);
			CHECK_FALSE(s1 <= s2);
		}

		SUBCASE("Distinct sets") {
			const int list2[] = { 5, 10, 42 };
			const int listSize2{ 3 };
			const Set s2{ list2, listSize2 };

			CHECK_FALSE(s1 <= s2);
			CHECK_FALSE(s2 <= s1);
		}
	}
	//No memory leaks
} //glöm ej att ta fram!!!!!!*/

///***************************************************
// * TEST PHASE 5: More complicated set expressions  *
// ***************************************************/
//
TEST_SUITE("Phase 5: Insertion Deletion") {

	TEST_CASE("Set operations test 1") {
		const int list[] = { 4, 3, 2, 11, 9 };
		const int listSize{ 5 };

		const Set s1{ list, listSize };
		const Set s2{ s1 - 2 + 1 - 9999 };

		SUBCASE("Check set cardinality") {
			CHECK(s2.cardinality() == 5);
		}

		SUBCASE("Check set members") {
			CHECK(s2.member(4));
			CHECK(s2.member(3));
			CHECK(s2.member(1));
			CHECK(s2.member(11));
			CHECK(s2.member(9));
		}

		SUBCASE("Check set members sorting") {
			std::ostringstream os;
			os << s2;

			CHECK(os.str() == std::string("{ 1 3 4 9 11 }"));
		}
	}

	TEST_CASE("Set operations test 2") {
		const int list[] = { 1, 3, 5 };
		const int listSize{ 3 };

		const Set s1{ list, listSize };
		const Set s2{ s1 + 4 - 5 - 9999 + 999 - s1 };

		SUBCASE("Check set cardinality") {
			CHECK(s2.cardinality() == 2);
		}

		SUBCASE("Check set members") {
			CHECK(s2.member(4));
			CHECK(s2.member(999));
		}

		SUBCASE("Check set members sorting") {
			std::ostringstream os;
			os << s2;

			CHECK(os.str() == std::string("{ 4 999 }"));
		}
	}
}