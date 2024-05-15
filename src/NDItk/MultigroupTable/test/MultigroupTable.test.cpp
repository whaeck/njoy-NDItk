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
std::string chunkWithMissingRecords();

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
      multigroup::EnergyGroupStructure structure( { 20., 18.123456789, 16.0000000000001,
                                                    14., 10., 5, 1, 1e-11 } );
      std::vector< multigroup::EnergyGroupStructure > outgoing =   {
          { 0, { 20., 10., 5, 1e-11 } },
          { 1001, { 20., 10., 1e-11 } }
      };
      multigroup::Velocities velocities( { 2.1, 2.2, 2.25, 2.05, 2.15, 2.04, 2.06 } );
      multigroup::FluxWeights weights( { 0.1, 0.2, 0.25, 0.05, 0.15, 0.04, 0.06 } );
      multigroup::TotalCrossSection total( { 1.1, 1.2, 1.25, 1.05, 1.15, 1.04, 1.06 } );
      multigroup::ReactionCrossSections xs( { { 2, 0.0, { 10., 20., 30., 40., 50., 60., 70. } },
                                              { 16, 1.1234567, { 1., 2., 3., 4., 5., 6., 7. } } } );
      multigroup::AverageFissionEnergyRelease release( 202.827, 181.238898, 4.827645,
                                                       7.281253, 6.5, 169.13 );

      MultigroupTable chunk( std::move( zaid ), std::move( name ),
                             std::move( process ), awr, temperature, dilution,
                             std::move( structure ), std::move( outgoing ),
                             std::move( velocities ), std::move( weights ),
                             std::move( xs ), std::move( source ), weight,
                             std::move( total ), std::move( release ) );

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

    WHEN( "required records are missing" ) {

      std::string record = chunkWithMissingRecords();
      auto iter = record.begin();
      auto end = record.end();

      MultigroupTable chunk;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( chunk.read( iter, end ) );
      } // THEN
    } // WHEN

    WHEN( "the number of groups is inconsistent" ) {

      std::string zaid = "92235.711nm";
      std::string name = "mendf71x";
      std::string source = "12/22/2011";
      std::string process = "08/07/2013";
      double awr = 233.0248;
      double weight = 235.043937521619;
      double temperature = 2.53e-8;
      double dilution = 1e+10;
      multigroup::EnergyGroupStructure structure( { 20., 18., 16., 14., 10., 5, 1, 1e-11 } );            // <-- 7 groups
      multigroup::Velocities velocities( { 2.1, 2.2, 2.25, 2.05 } );                                     // <-- 4 groups
      multigroup::FluxWeights weights( { 0.1, 0.2, 0.25, 0.05, 0.15, 0.04 } );                           // <-- 6 groups
      multigroup::TotalCrossSection total( { 1.1, 1.2, 1.25, 1.05, 1.15, 1.04 } );                       // <-- 5 groups
      multigroup::ReactionCrossSections xs( { { 2, 0.0, { 10., 20., 30., 40., 50., 60., 70., 80. } },    // <-- 8 groups
                                              { 16, 1.1234567, { 1., 2., 3., 4., 5., 6., 7., 8. } } } );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( MultigroupTable( std::move( zaid ), std::move( name ),
                                       std::move( process ), awr, temperature, dilution,
                                       std::move( structure ), {}, std::move( velocities ),
                                       std::move( weights ), std::move( xs ),
                                       std::move( source ), weight,
                                       std::move( total ) ) );
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
         "num_grps_0\n"
         "    3\n"
         "num_grps_1001\n"
         "    2\n"
         "num_reac\n"
         "    2\n"
         "e_bounds\n"
         "    20 18.123456789 16.0000000000001 14 10\n"
         "    5 1 1e-11\n"
         "e_bounds_0\n"
         "    20 10 5 1e-11\n"
         "e_bounds_1001\n"
         "    20 10 1e-11\n"
         "vel\n"
         "    2.1 2.2 2.25 2.05 2.15\n"
         "    2.04 2.06\n"
         "wgts\n"
         "    0.1 0.2 0.25 0.05 0.15\n"
         "    0.04 0.06\n"
         "sig_tot\n"
         "    1.1 1.2 1.25 1.05 1.15\n"
         "    1.04 1.06\n"
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
  auto structure = chunk.primaryGroupBoundaries();
  CHECK( "e_bounds" == structure.keyword() );
  CHECK( std::nullopt == structure.particle() );
  CHECK( false == structure.empty() );
  CHECK( 8 == structure.size() );
  CHECK( 8 == structure.values().size() );
  CHECK( 7 == structure.numberGroups() );
  CHECK_THAT(    20, WithinRel( structure.values()[0] ) );
  CHECK_THAT(    18.123456789, WithinRel( structure.values()[1] ) );
  CHECK_THAT(    16.0000000000001, WithinRel( structure.values()[2] ) );
  CHECK_THAT(    14, WithinRel( structure.values()[3] ) );
  CHECK_THAT(    10, WithinRel( structure.values()[4] ) );
  CHECK_THAT(     5, WithinRel( structure.values()[5] ) );
  CHECK_THAT(     1, WithinRel( structure.values()[6] ) );
  CHECK_THAT( 1e-11, WithinRel( structure.values()[7] ) );

  // outgoing group structure: 0
  structure = chunk.outgoingGroupBoundaries( 0 );
  CHECK( "e_bounds_0" == structure.keyword() );
  CHECK( 0 == structure.particle() );
  CHECK( false == structure.empty() );
  CHECK( 4 == structure.size() );
  CHECK( 4 == structure.values().size() );
  CHECK( 3 == structure.numberGroups() );
  CHECK_THAT(    20, WithinRel( structure.values()[0] ) );
  CHECK_THAT(    10, WithinRel( structure.values()[1] ) );
  CHECK_THAT(     5, WithinRel( structure.values()[2] ) );
  CHECK_THAT( 1e-11, WithinRel( structure.values()[3] ) );

  // outgoing group structure: 1001
  structure = chunk.outgoingGroupBoundaries( 1001 );
  CHECK( "e_bounds_1001" == structure.keyword() );
  CHECK( 1001 == structure.particle() );
  CHECK( false == structure.empty() );
  CHECK( 3 == structure.size() );
  CHECK( 3 == structure.values().size() );
  CHECK( 2 == structure.numberGroups() );
  CHECK_THAT(    20, WithinRel( structure.values()[0] ) );
  CHECK_THAT(    10, WithinRel( structure.values()[1] ) );
  CHECK_THAT( 1e-11, WithinRel( structure.values()[2] ) );

  // velocity values
  auto velocities = chunk.velocities();
  CHECK( "vel" == velocities.keyword() );
  CHECK( false == velocities.empty() );
  CHECK( 7 == velocities.size() );
  CHECK( 7 == velocities.values().size() );
  CHECK( 7 == velocities.numberGroups() );
  CHECK_THAT( 2.10, WithinRel( velocities.values()[0] ) );
  CHECK_THAT( 2.20, WithinRel( velocities.values()[1] ) );
  CHECK_THAT( 2.25, WithinRel( velocities.values()[2] ) );
  CHECK_THAT( 2.05, WithinRel( velocities.values()[3] ) );
  CHECK_THAT( 2.15, WithinRel( velocities.values()[4] ) );
  CHECK_THAT( 2.04, WithinRel( velocities.values()[5] ) );
  CHECK_THAT( 2.06, WithinRel( velocities.values()[6] ) );

  // flux values
  auto flux = chunk.fluxWeights();
  CHECK( "wgts" == flux.keyword() );
  CHECK( false == flux.empty() );
  CHECK( 7 == flux.size() );
  CHECK( 7 == flux.values().size() );
  CHECK( 7 == flux.numberGroups() );
  CHECK_THAT( 0.10, WithinRel( flux.values()[0] ) );
  CHECK_THAT( 0.20, WithinRel( flux.values()[1] ) );
  CHECK_THAT( 0.25, WithinRel( flux.values()[2] ) );
  CHECK_THAT( 0.05, WithinRel( flux.values()[3] ) );
  CHECK_THAT( 0.15, WithinRel( flux.values()[4] ) );
  CHECK_THAT( 0.04, WithinRel( flux.values()[5] ) );
  CHECK_THAT( 0.06, WithinRel( flux.values()[6] ) );

  // total cross section
  CHECK( "sig_tot" == chunk.totalCrossSection().keyword() );
  CHECK( false == chunk.totalCrossSection().empty() );
  CHECK( 7 == chunk.totalCrossSection().size() );
  CHECK( 7 == chunk.totalCrossSection().values().size() );
  CHECK( 7 == chunk.totalCrossSection().numberGroups() );
  CHECK_THAT( 1.10, WithinRel( chunk.totalCrossSection().values()[0] ) );
  CHECK_THAT( 1.20, WithinRel( chunk.totalCrossSection().values()[1] ) );
  CHECK_THAT( 1.25, WithinRel( chunk.totalCrossSection().values()[2] ) );
  CHECK_THAT( 1.05, WithinRel( chunk.totalCrossSection().values()[3] ) );
  CHECK_THAT( 1.15, WithinRel( chunk.totalCrossSection().values()[4] ) );
  CHECK_THAT( 1.04, WithinRel( chunk.totalCrossSection().values()[5] ) );
  CHECK_THAT( 1.06, WithinRel( chunk.totalCrossSection().values()[6] ) );

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

std::string chunkWithMissingRecords() {

  // e_bounds and wgts are not present
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
         "num_grps_0\n"
         "    3\n"
         "num_grps_1001\n"
         "    2\n"
         "num_reac\n"
         "    2\n"
         "e_bounds_0\n"
         "    20 10 5 1e-11\n"
         "e_bounds_1001\n"
         "    20 10 1e-11\n"
         "vel\n"
         "    2.1 2.2 2.25 2.05 2.15\n"
         "    2.04 2.06\n"
         "sig_tot\n"
         "    1.1 1.2 1.25 1.05 1.15\n"
         "    1.04 1.06\n"
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
