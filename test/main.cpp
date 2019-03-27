#define CATCH_CONFIG_MAIN 
#include <catch2/catch.hpp>
#include "html.hpp"


TEST_CASE( "HTML is rendered.", "[HTML]" ) {
  REQUIRE( renderstring(hr({}, {})) == "<hr></hr>" );
}


