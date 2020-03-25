
//Bring in unit testing code
#include "../Catch2/single_include/catch2/catch.hpp"

//Include your .h files
#include <iostream>

using namespace std;

TEST_CASE("Sample Test") {
    cout << "Sample Test Case" << endl;

    SECTION( "Section 1" ) {
        REQUIRE(false == false);
    }

    SECTION( "Section 2" ) {
        REQUIRE(1 == 1);
    }
}
