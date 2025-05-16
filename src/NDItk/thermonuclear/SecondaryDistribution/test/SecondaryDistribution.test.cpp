// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/thermonuclear/SecondaryDistribution.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using EnergyDistribution = thermonuclear::EnergyDistribution;
using SecondaryDistribution = thermonuclear::SecondaryDistribution;

SCENARIO( "SecondaryDistribution" ) {

  GIVEN( "valid data for a SecondaryDistribution instance" ) {

    WHEN( "the data is given explicitly" ) {

      SecondaryDistribution chunk;

    } // WHEN
  } // GIVEN

} // SCENARIO
