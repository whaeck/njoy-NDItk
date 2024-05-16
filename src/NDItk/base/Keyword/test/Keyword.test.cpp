// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/base/Keyword.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using Keyword = base::Keyword;

SCENARIO( "Keyword" ) {

  Keyword result( "num_grps" );
  CHECK( "num_grps" == result.keyword() );
  CHECK( std::nullopt == result.subtype() );
  CHECK( std::nullopt == result.particle() );
  CHECK( false == result.hasSubtype() );

  result = Keyword( "num_grps_0" );
  CHECK( "num_grps_0" == result.keyword() );
  CHECK( "num_grps" == result.subtype() );
  CHECK( 0 == result.particle() );
  CHECK( true == result.hasSubtype() );

  result = Keyword( "num_grps", 0 );
  CHECK( "num_grps_0" == result.keyword() );
  CHECK( "num_grps" == result.subtype() );
  CHECK( 0 == result.particle() );
  CHECK( true == result.hasSubtype() );

  result = Keyword( "e_bounds_1001" );
  CHECK( "e_bounds_1001" == result.keyword() );
  CHECK( "e_bounds" == result.subtype() );
  CHECK( 1001 == result.particle() );
  CHECK( true == result.hasSubtype() );

  result = Keyword( "e_bounds", 1001 );
  CHECK( "e_bounds_1001" == result.keyword() );
  CHECK( "e_bounds" == result.subtype() );
  CHECK( 1001 == result.particle() );
  CHECK( true == result.hasSubtype() );

  result = Keyword( "sig_0" );
  CHECK( "sig_0" == result.keyword() );
  CHECK( std::nullopt == result.subtype() );
  CHECK( std::nullopt == result.particle() );
  CHECK( false == result.hasSubtype() );

  result = Keyword( "num_sec_parts" );
  CHECK( "num_sec_parts" == result.keyword() );
  CHECK( std::nullopt == result.subtype() );
  CHECK( std::nullopt == result.particle() );
  CHECK( false == result.hasSubtype() );

  CHECK_THROWS( Keyword( "NuM_GrPs" ) );
} // SCENARIO
