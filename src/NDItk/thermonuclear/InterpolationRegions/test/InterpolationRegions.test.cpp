// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/thermonuclear/InterpolationRegions.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using InterpolationRegions = thermonuclear::InterpolationRegions;

SCENARIO( "InterpolationRegions" ) {

  GIVEN( "valid data for an InterpolationRegions instance" ) {

    WHEN( "the data is given explicitly" ) {

      InterpolationRegions chunk;
    } // WHEN
  } // GIVEN

} // SCENARIO
