// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/MultigroupTable.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;

std::string chunk();
void verifyChunk( const MultigroupTable& );

SCENARIO( "MultigroupTable" ) {

  GIVEN( "valid data for a MultigroupTable instance" ) {

    std::string record = chunk();

    WHEN( "the data is read using iterators" ) {

      auto iter = record.begin();
      auto end = record.end();

      MultigroupTable chunk;
      chunk.read( iter, end );

      THEN( "a MultigroupTable can be constructed and members can "
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

  return "zaid\n"
         "    92235.711nm\n"
         "library_name\n"
         "    mendf71x\n"
         "date_source\n"
         "    12/22/2011\n"
         "date_processed\n"
         "    08/07/2013\n"
         "awr\n"
         "            233.0248\n"
         "at_wgt\n"
         "    235.043937521619\n"
         "temp\n"
         "            2.53e-08\n"
         "sig_0\n"
         "         10000000000\n"
         "num_grps\n"
         "                   7\n"
         "up_grps\n"
         "                   0\n"
         "down_grps\n"
         "                   6\n"
         "pn_order\n"
         "                   5\n"
         "e_bounds\n"
         "                  20                  18                  16                  14\n"
         "                  10                   5                   1               1e-11\n"
         "end\n";
}

void verifyChunk( const MultigroupTable& chunk ) {

  CHECK( "92235.711nm" == chunk.metadata().zaid().value() );
  CHECK( "mendf71x" == chunk.metadata().libraryName().value() );
  CHECK( "12/22/2011" == chunk.metadata().sourceData().value() );
  CHECK( "08/07/2013" == chunk.metadata().processDate().value() );
  CHECK_THAT( 233.0248, WithinRel( chunk.metadata().atomicWeightRatio().value() ) );
  CHECK_THAT( 235.043937521619, WithinRel( chunk.metadata().atomicWeight().value() ) );
  CHECK_THAT( 2.53e-8, WithinRel( chunk.metadata().temperature().value() ) );
  CHECK_THAT( 1e+10, WithinRel( chunk.metadata().dilution().value() ) );
  CHECK( 7 == chunk.metadata().numberGroups().value() );
  CHECK( 6 == chunk.metadata().numberDownscatterGroups().value() );
  CHECK( 0 == chunk.metadata().numberUpscatterGroups().value() );
  CHECK( 5 == chunk.metadata().legendreOrder().value() );
}
