// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/multigroup/Metadata.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using Metadata = multigroup::Metadata;

std::string chunk();
void verifyChunk( const Metadata& );

SCENARIO( "Metadata" ) {

  GIVEN( "valid data for a Metadata instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      double awr = 233.0248;
      double weight = 235.0439375216192;
      double temperature = 2.53e-8;
      double dilution = 1e+10;
      unsigned int groups = 618;
      unsigned int upscatter = 0;
      unsigned int downscatter = 617;
      unsigned int order = 5;
      Metadata chunk( awr, weight, temperature, dilution,
                      groups, upscatter, downscatter, order  );

      THEN( "a Metadata can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "the record can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output );

        CHECK( buffer == record );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return "awr\n"
         "            233.0248\n"
         "at_wgt\n"
         "   235.0439375216192\n"
         "temp\n"
         "            2.53e-08\n"
         "sig_0\n"
         "         10000000000\n"
         "num_grps\n"
         "                 618\n"
         "up_grps\n"
         "                   0\n"
         "down_grps\n"
         "                 617\n"
         "pn_order\n"
         "                   5\n";
}

void verifyChunk( const Metadata& chunk ) {

  CHECK_THAT( 233.0248, WithinRel( chunk.atomicWeightRatio().value() ) );
  CHECK_THAT( 235.0439375216192, WithinRel( chunk.atomicWeight().value() ) );
  CHECK_THAT( 2.53e-8, WithinRel( chunk.temperature().value() ) );
  CHECK_THAT( 1e+10, WithinRel( chunk.dilution().value() ) );
  CHECK( 618 == chunk.numberGroups().value() );
  CHECK( 617 == chunk.numberDownscatterGroups().value() );
  CHECK(   0 == chunk.numberUpscatterGroups().value() );
  CHECK(   5 == chunk.legendreOrder().value() );
}
