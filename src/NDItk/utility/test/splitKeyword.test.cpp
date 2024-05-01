// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/utility/splitKeyword.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;

SCENARIO( "splitKeyword" ) {

  GIVEN( "valid keys" ) {

    auto result = utility::splitKeyword( "num_grps" );
    CHECK( result.first == "num_grps" );
    CHECK( result.second == std::nullopt );

  } // GIVEN
} // SCENARIO

