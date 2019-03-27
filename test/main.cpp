#define CATCH_CONFIG_MAIN 
#include <catch2/catch.hpp>
#include "html.hpp"


TEST_CASE( "Factorials are computed", "[factorial]" ) {
  REQUIRE( render() == "<hr/>" );
}


