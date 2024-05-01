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

    WHEN( "the data is given explicitly" ) {

      std::string zaid = "92235.711nm";
      std::string name = "mendf71x";
      std::string source = "12/22/2011";
      std::string process = "08/07/2013";
      double awr = 233.0248;
      double weight = 235.043937521619;
      double temperature = 2.53e-8;
      double dilution = 1e+10;
      multigroup::EnergyGroupStructure structure( { 20., 18., 16., 14., 10., 5, 1, 1e-11 } );
      multigroup::FluxWeights weights( { 0.1, 0.2, 0.25, 0.05, 0.15, 0.04, 0.06 } );
      multigroup::ReactionCrossSections xs( { { 2, 0.0, { 10., 20., 30., 40., 50., 60., 70. } },
                                              { 16, 1.1234567, { 1., 2., 3., 4., 5., 6., 7. } } } );
      multigroup::AverageFissionEnergyRelease release( 202.827, 181.238898, 4.827645,
                                                       7.281253, 6.5, 169.13 );

      MultigroupTable chunk( std::move( zaid ), std::move( name ), std::move( source ),
                             std::move( process ), awr, weight, temperature, dilution,
                             std::move( structure ), std::move( weights ), std::move( xs ),
                             std::move( release ) );

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

  GIVEN( "invalid data for a MultigroupTable instance" ) {

    WHEN( "the number of groups is inconsistent" ) {

      std::string zaid = "92235.711nm";
      std::string name = "mendf71x";
      std::string source = "12/22/2011";
      std::string process = "08/07/2013";
      double awr = 233.0248;
      double weight = 235.043937521619;
      double temperature = 2.53e-8;
      double dilution = 1e+10;
      multigroup::EnergyGroupStructure structure( { 20., 18., 16., 14., 10., 5, 1, 1e-11 } );                       // <-- 7 groups
      multigroup::FluxWeights weights( { 0.1, 0.2, 0.25, 0.05, 0.15, 0.04 } );                           // <-- 6 groups
      multigroup::ReactionCrossSections xs( { { 2, 0.0, { 10., 20., 30., 40., 50., 60., 70., 80. } },    // <-- 8 groups
                                              { 16, 1.1234567, { 1., 2., 3., 4., 5., 6., 7., 8. } } } );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( MultigroupTable( std::move( zaid ), std::move( name ), std::move( source ),
                                       std::move( process ), awr, weight, temperature, dilution,
                                       std::move( structure ), std::move( weights ), std::move( xs ) ) );
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
         "    233.0248\n"
         "at_wgt\n"
         "    235.043937521619\n"
         "temp\n"
         "    2.53e-08\n"
         "sig_0\n"
         "    10000000000\n"
         "num_grps\n"
         "    7\n"
         "num_reac\n"
         "    2\n"
         "e_bounds\n"
         "    20 18 16 14 10\n"
         "    5 1 1e-11\n"
         "wgts\n"
         "    0.1 0.2 0.25 0.05 0.15\n"
         "    0.04 0.06\n"
         "sig_reac\n"
         "    2 0\n"
         "    10 20 30 40 50\n"
         "    60 70\n"
         "    16 1.1234567\n"
         "    1 2 3 4 5\n"
         "    6 7\n"
         "fiss_q\n"
         "    181.238898 202.827 6.5 7.281253 169.13\n"
         "    4.827645\n"
         "end\n";
}

void verifyChunk( const MultigroupTable& chunk ) {

  // metadata
  CHECK( "92235.711nm" == chunk.metadata().zaid().value() );
  CHECK( "mendf71x" == chunk.metadata().libraryName().value() );
  CHECK( "12/22/2011" == chunk.metadata().sourceDate().value() );
  CHECK( "08/07/2013" == chunk.metadata().processDate().value() );
  CHECK_THAT( 233.0248, WithinRel( chunk.metadata().atomicWeightRatio().value() ) );
  CHECK_THAT( 235.043937521619, WithinRel( chunk.metadata().atomicWeight().value() ) );
  CHECK_THAT( 2.53e-8, WithinRel( chunk.metadata().temperature().value() ) );
  CHECK_THAT( 1e+10, WithinRel( chunk.metadata().dilution().value() ) );
  CHECK( 7 == chunk.metadata().numberGroups().value() );
  CHECK( 2 == chunk.metadata().numberReactions().value() );

  // principal group structure
  CHECK( "e_bounds" == chunk.structure().keyword() );
  CHECK( false == chunk.structure().empty() );
  CHECK( 8 == chunk.structure().size() );
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
  CHECK( false == chunk.flux().empty() );
  CHECK( 7 == chunk.flux().size() );
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
  CHECK( 18 == chunk.reactionCrossSections().size() );
  CHECK( false == chunk.reactionCrossSections().empty() );
  CHECK( 2 == chunk.reactionCrossSections().numberReactions() );
  CHECK( 7 == chunk.reactionCrossSections().numberGroups() );
  CHECK( true == chunk.reactionCrossSections().hasReaction( 2 ) );
  CHECK( true == chunk.reactionCrossSections().hasReaction( 16 ) );
  CHECK( false == chunk.reactionCrossSections().hasReaction( 102 ) );
  CHECK( false == chunk.reactionCrossSections().reactions()[0].empty() );
  CHECK( 9 == chunk.reactionCrossSections().reactions()[0].size() );
  CHECK( 7 == chunk.reactionCrossSections().reactions()[0].numberGroups() );
  CHECK( 2 == chunk.reactionCrossSections().reactions()[0].identifier() );
  CHECK_THAT( 0.0, WithinRel( chunk.reactionCrossSections().reactions()[0].qvalue() ) );
  CHECK_THAT( 10.0, WithinRel( chunk.reactionCrossSections().reactions()[0].crossSections()[0] ) );
  CHECK_THAT( 20.0, WithinRel( chunk.reactionCrossSections().reactions()[0].crossSections()[1] ) );
  CHECK_THAT( 30.0, WithinRel( chunk.reactionCrossSections().reactions()[0].crossSections()[2] ) );
  CHECK_THAT( 40.0, WithinRel( chunk.reactionCrossSections().reactions()[0].crossSections()[3] ) );
  CHECK_THAT( 50.0, WithinRel( chunk.reactionCrossSections().reactions()[0].crossSections()[4] ) );
  CHECK_THAT( 60.0, WithinRel( chunk.reactionCrossSections().reactions()[0].crossSections()[5] ) );
  CHECK_THAT( 70.0, WithinRel( chunk.reactionCrossSections().reactions()[0].crossSections()[6] ) );
  CHECK( false == chunk.reactionCrossSections().reactions()[1].empty() );
  CHECK( 9 == chunk.reactionCrossSections().reactions()[1].size() );
  CHECK( 7 == chunk.reactionCrossSections().reactions()[1].numberGroups() );
  CHECK( 16 == chunk.reactionCrossSections().reactions()[1].identifier() );
  CHECK_THAT( 1.1234567, WithinRel( chunk.reactionCrossSections().reactions()[1].qvalue() ) );
  CHECK_THAT( 1.0, WithinRel( chunk.reactionCrossSections().reactions()[1].crossSections()[0] ) );
  CHECK_THAT( 2.0, WithinRel( chunk.reactionCrossSections().reactions()[1].crossSections()[1] ) );
  CHECK_THAT( 3.0, WithinRel( chunk.reactionCrossSections().reactions()[1].crossSections()[2] ) );
  CHECK_THAT( 4.0, WithinRel( chunk.reactionCrossSections().reactions()[1].crossSections()[3] ) );
  CHECK_THAT( 5.0, WithinRel( chunk.reactionCrossSections().reactions()[1].crossSections()[4] ) );
  CHECK_THAT( 6.0, WithinRel( chunk.reactionCrossSections().reactions()[1].crossSections()[5] ) );
  CHECK_THAT( 7.0, WithinRel( chunk.reactionCrossSections().reactions()[1].crossSections()[6] ) );
  auto xs = chunk.reactionCrossSections().reaction( 2 );
  CHECK( false == xs.empty() );
  CHECK( 9 == xs.size() );
  CHECK( 7 == xs.numberGroups() );
  CHECK( 2 == xs.identifier() );
  CHECK_THAT( 0.0, WithinRel( xs.qvalue() ) );
  CHECK_THAT( 10.0, WithinRel( xs.crossSections()[0] ) );
  CHECK_THAT( 20.0, WithinRel( xs.crossSections()[1] ) );
  CHECK_THAT( 30.0, WithinRel( xs.crossSections()[2] ) );
  CHECK_THAT( 40.0, WithinRel( xs.crossSections()[3] ) );
  CHECK_THAT( 50.0, WithinRel( xs.crossSections()[4] ) );
  CHECK_THAT( 60.0, WithinRel( xs.crossSections()[5] ) );
  CHECK_THAT( 70.0, WithinRel( xs.crossSections()[6] ) );
  xs = chunk.reactionCrossSections().reaction( 16 );
  CHECK( false == xs.empty() );
  CHECK( 9 == xs.size() );
  CHECK( 7 == xs.numberGroups() );
  CHECK( 16 == xs.identifier() );
  CHECK_THAT( 1.1234567, WithinRel( xs.qvalue() ) );
  CHECK_THAT( 1.0, WithinRel( xs.crossSections()[0] ) );
  CHECK_THAT( 2.0, WithinRel( xs.crossSections()[1] ) );
  CHECK_THAT( 3.0, WithinRel( xs.crossSections()[2] ) );
  CHECK_THAT( 4.0, WithinRel( xs.crossSections()[3] ) );
  CHECK_THAT( 5.0, WithinRel( xs.crossSections()[4] ) );
  CHECK_THAT( 6.0, WithinRel( xs.crossSections()[5] ) );
  CHECK_THAT( 7.0, WithinRel( xs.crossSections()[6] ) );

  // average fission energy release
  CHECK( "fiss_q" == chunk.averageFissionEnergyRelease().keyword() );
  CHECK( false == chunk.averageFissionEnergyRelease().empty() );
  CHECK( 6 == chunk.averageFissionEnergyRelease().size() );
  CHECK_THAT( 181.238898, WithinRel( chunk.averageFissionEnergyRelease().promptEnergyRelease() ) );
  CHECK_THAT(    202.827, WithinRel( chunk.averageFissionEnergyRelease().totalEnergyRelease() ) );
  CHECK_THAT(        6.5, WithinRel( chunk.averageFissionEnergyRelease().delayedBetas() ) );
  CHECK_THAT(   7.281253, WithinRel( chunk.averageFissionEnergyRelease().promptGammas() ) );
  CHECK_THAT(     169.13, WithinRel( chunk.averageFissionEnergyRelease().fissionFragments() ) );
  CHECK_THAT(   4.827645, WithinRel( chunk.averageFissionEnergyRelease().promptNeutrons() ) );
}
