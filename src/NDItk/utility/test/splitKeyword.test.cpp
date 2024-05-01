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

    result = utility::splitKeyword( "num_grps_0" );
    CHECK( result.first == "num_grps" );
    CHECK( result.second == 0 );

    result = utility::splitKeyword( "e_bounds_1001" );
    CHECK( result.first == "e_bounds" );
    CHECK( result.second == 1001 );

    CHECK_THROWS( utility::splitKeyword( "NuM_GrPs" ) );

  } // GIVEN
} // SCENARIO

