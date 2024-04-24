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
         "num_reac\n"
         "                   2\n"
         "e_bounds\n"
         "                  20                  18                  16                  14\n"
         "                  10                   5                   1               1e-11\n"
         "wgts\n"
         "                 0.1                 0.2                0.25                0.05\n"
         "                0.15                0.04                0.06\n"
         "sig_reac\n"
         "                   2                   0\n"
         "                  10                  20                  30                  40\n"
         "                  50                  60                  70\n"
         "                  16           1.1234567\n"
         "                   1                   2                   3                   4\n"
         "                   5                   6                   7\n"
         "end\n";
}

void verifyChunk( const MultigroupTable& chunk ) {

  // metadata
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

  // principal group structure
  CHECK( "e_bounds" == chunk.structure().keyword() );
  CHECK( true == chunk.structure().hasContent() );
  CHECK( 8 == chunk.structure().boundaries().size() );
  CHECK( 7 == chunk.structure().numberGroups() );
  CHECK_THAT(    20, WithinRel( chunk.structure().boundaries()[0] ) );
  CHECK_THAT(    18, WithinRel( chunk.structure().boundaries()[1] ) );
  CHECK_THAT(    16, WithinRel( chunk.structure().boundaries()[2] ) );
  CHECK_THAT(    14, WithinRel( chunk.structure().boundaries()[3] ) );
  CHECK_THAT(    10, WithinRel( chunk.structure().boundaries()[4] ) );
  CHECK_THAT(     5, WithinRel( chunk.structure().boundaries()[5] ) );
  CHECK_THAT(     1, WithinRel( chunk.structure().boundaries()[6] ) );
  CHECK_THAT( 1e-11, WithinRel( chunk.structure().boundaries()[7] ) );

  // flux weights
  CHECK( "wgts" == chunk.flux().keyword() );
  CHECK( true == chunk.flux().hasContent() );
  CHECK( 7 == chunk.flux().weights().size() );
  CHECK( 7 == chunk.flux().numberGroups() );
  CHECK_THAT( 0.10, WithinRel( chunk.flux().weights()[0] ) );
  CHECK_THAT( 0.20, WithinRel( chunk.flux().weights()[1] ) );
  CHECK_THAT( 0.25, WithinRel( chunk.flux().weights()[2] ) );
  CHECK_THAT( 0.05, WithinRel( chunk.flux().weights()[3] ) );
  CHECK_THAT( 0.15, WithinRel( chunk.flux().weights()[4] ) );
  CHECK_THAT( 0.04, WithinRel( chunk.flux().weights()[5] ) );
  CHECK_THAT( 0.06, WithinRel( chunk.flux().weights()[6] ) );

  // reaction cross sections
  CHECK( true == chunk.crossSections().hasContent() );
  CHECK( 2 == chunk.crossSections().numberReactions() );
  CHECK( 7 == chunk.crossSections().numberGroups() );
  CHECK( true == chunk.crossSections().hasReaction( 2 ) );
  CHECK( true == chunk.crossSections().hasReaction( 16 ) );
  CHECK( false == chunk.crossSections().hasReaction( 102 ) );
  CHECK( 2 == chunk.crossSections().reactions()[0].reaction() );
  CHECK_THAT( 0.0, WithinRel( chunk.crossSections().reactions()[0].qvalue() ) );
  CHECK_THAT( 10.0, WithinRel( chunk.crossSections().reactions()[0].crossSections()[0] ) );
  CHECK_THAT( 20.0, WithinRel( chunk.crossSections().reactions()[0].crossSections()[1] ) );
  CHECK_THAT( 30.0, WithinRel( chunk.crossSections().reactions()[0].crossSections()[2] ) );
  CHECK_THAT( 40.0, WithinRel( chunk.crossSections().reactions()[0].crossSections()[3] ) );
  CHECK_THAT( 50.0, WithinRel( chunk.crossSections().reactions()[0].crossSections()[4] ) );
  CHECK_THAT( 60.0, WithinRel( chunk.crossSections().reactions()[0].crossSections()[5] ) );
  CHECK_THAT( 70.0, WithinRel( chunk.crossSections().reactions()[0].crossSections()[6] ) );
  CHECK( 16 == chunk.crossSections().reactions()[1].reaction() );
  CHECK_THAT( 1.1234567, WithinRel( chunk.crossSections().reactions()[1].qvalue() ) );
  CHECK_THAT( 1.0, WithinRel( chunk.crossSections().reactions()[1].crossSections()[0] ) );
  CHECK_THAT( 2.0, WithinRel( chunk.crossSections().reactions()[1].crossSections()[1] ) );
  CHECK_THAT( 3.0, WithinRel( chunk.crossSections().reactions()[1].crossSections()[2] ) );
  CHECK_THAT( 4.0, WithinRel( chunk.crossSections().reactions()[1].crossSections()[3] ) );
  CHECK_THAT( 5.0, WithinRel( chunk.crossSections().reactions()[1].crossSections()[4] ) );
  CHECK_THAT( 6.0, WithinRel( chunk.crossSections().reactions()[1].crossSections()[5] ) );
  CHECK_THAT( 7.0, WithinRel( chunk.crossSections().reactions()[1].crossSections()[6] ) );
  auto xs = chunk.crossSections().crossSection( 2 );
  CHECK( 2 == xs.reaction() );
  CHECK_THAT( 0.0, WithinRel( xs.qvalue() ) );
  CHECK_THAT( 10.0, WithinRel( xs.crossSections()[0] ) );
  CHECK_THAT( 20.0, WithinRel( xs.crossSections()[1] ) );
  CHECK_THAT( 30.0, WithinRel( xs.crossSections()[2] ) );
  CHECK_THAT( 40.0, WithinRel( xs.crossSections()[3] ) );
  CHECK_THAT( 50.0, WithinRel( xs.crossSections()[4] ) );
  CHECK_THAT( 60.0, WithinRel( xs.crossSections()[5] ) );
  CHECK_THAT( 70.0, WithinRel( xs.crossSections()[6] ) );
  xs = chunk.crossSections().crossSection( 16 );
  CHECK( 16 == xs.reaction() );
  CHECK_THAT( 1.1234567, WithinRel( xs.qvalue() ) );
  CHECK_THAT( 1.0, WithinRel( xs.crossSections()[0] ) );
  CHECK_THAT( 2.0, WithinRel( xs.crossSections()[1] ) );
  CHECK_THAT( 3.0, WithinRel( xs.crossSections()[2] ) );
  CHECK_THAT( 4.0, WithinRel( xs.crossSections()[3] ) );
  CHECK_THAT( 5.0, WithinRel( xs.crossSections()[4] ) );
  CHECK_THAT( 6.0, WithinRel( xs.crossSections()[5] ) );
  CHECK_THAT( 7.0, WithinRel( xs.crossSections()[6] ) );
}
