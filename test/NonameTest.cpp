
#include <boost/test/unit_test.hpp>
#include <vector>
#include <algorithm>

/*
BOOST_AUTO_TEST_CASE( my_test )
{
  // seven ways to detect and report the same error:
  BOOST_CHECK( add( 2,2 ) == 4 );        // #1 continues on error
  BOOST_REQUIRE( add( 2,2 ) == 4 );      // #2 throws on error

  if( add( 2,2 ) != 4 )
     BOOST_ERROR( "Ouch..." );            // #3 continues on error

  if( add( 2,2 ) != 4 )
    BOOST_FAIL( "Ouch..." );             // #4 throws on error

  if( add( 2,2 ) != 4 ) throw "Ouch..."; // #5 throws on error

  BOOST_CHECK_MESSAGE( add( 2,2 ) == 4,  // #6 continues on error
    "add(..) result: " << add( 2,2 ) );
  BOOST_CHECK_EQUAL( add( 2,2 ), 4 );      // #7 continues on error
}
*/

BOOST_AUTO_TEST_CASE( my_test )
{
	std::vector<int> v1;
	std::vector<int> v2;
	std::vector<int> v3;

	v1.push_back(1);
	v2.push_back(2);
	v1.push_back(2);
	v2.push_back(1);

	//std::vector<int>::iterator it = std::set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
	//std::sort(v1.begin(), v1.end());
	//std::sort(v2.begin(), v2.end());
	BOOST_CHECK( v1 == v2 );

}
