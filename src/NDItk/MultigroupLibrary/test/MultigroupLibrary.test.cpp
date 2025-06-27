// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/MultigroupTable.hpp"
#include "NDItk/MultigroupLibrary.hpp"

// other includes
#include <type_traits>

// convenience typedefs
using namespace njoy::NDItk;
using Library = njoy::NDItk::MultigroupLibrary;


std::string chunk();
void verifyChunk( const MultigroupLibrary& );
void verifySubChunk( const MultigroupTable& );

SCENARIO( "MultigroupLibrary" ) {

  GIVEN( "valid data for a MultigroupLibrary instance" ) {

    std::string record = chunk();

    WHEN( "the data is read using iterators" ) {

      auto iter = record.begin();
      auto end = record.end();

      MultigroupLibrary chunk;
      chunk.read( iter, end );

      THEN( "a MultigroupLibrary can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "the MultigroupLibrary record can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output );

        CHECK( buffer == record );
      } // THEN

      THEN( "the tables can be accessed" ) {

        CHECK( chunk.getTable("test_zaid_1").metadata().zaid() == "test_zaid_1" );
        CHECK( chunk.getTable("test_zaid_2").metadata().zaid() == "test_zaid_2" );
        CHECK( chunk.getTable("test_zaid_3").metadata().zaid() == "test_zaid_3" );

        verifySubChunk( chunk.getTable(0) );
        verifySubChunk( chunk.getTable(1) );
        verifySubChunk( chunk.getTable(2) );

      } // THEN
    } // WHEN
  } // GIVEN

} // SCENARIO

std::string chunk() {

  std::string header_str(
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.\n"
    "Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\n"
    "Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.\n"
    "Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.\n"
  );
  
  std::string zaid_str1("zaid\n    test_zaid_1\n");
  std::string zaid_str2("zaid\n    test_zaid_2\n");
  std::string zaid_str3("zaid\n    test_zaid_3\n");

  std::string table_str(
    "info\n"
    "    this is some information for the table\n"
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
    "pn_order\n"
    "    2\n"
    "num_sec_parts\n"
    "    2\n"
    "num_grps_0\n"
    "    3\n"
    "num_grps_1001\n"
    "    2\n"
    "pn_order_0\n"
    "    2\n"
    "pn_order_1001\n"
    "    2\n"
    "e_bounds\n"
    "    20 18.123456789 16.0000000000001 14 10\n"
    "    5 1 1e-11\n"
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
    "pn_full\n"
    "    0\n"
    "    0.999999999999 1e-13 0 0 0\n"
    "    0 0 0 1 0\n"
    "    0 0 0 0 0\n"
    "    0 1 0 0 0\n"
    "    0 0 0 0 1\n"
    "    0 0 0 0 0\n"
    "    0 0 1 0 0\n"
    "    0 0 0 0 0\n"
    "    1 0 0 0 0\n"
    "    0 0 0 1\n"
    "    1\n"
    "    0 0 0 0 0\n"
    "    0 1 0 0 0\n"
    "    0 0 1 0 0\n"
    "    0 0 0 1 0\n"
    "    0 0 0 0 1\n"
    "    0 0 0 0 0\n"
    "    1 0 0 0 0\n"
    "    0 1 0 0 0\n"
    "    0 0 1 0 0\n"
    "    0 0 0 0\n"
    "fiss_q\n"
    "    181.238898 202.827 6.5 7.281253 169.13\n"
    "    4.827645\n"
    "heating\n"
    "    11 22 33 44 55\n"
    "    66 77\n"
    "kerma\n"
    "    110 220 330 440 550\n"
    "    660 770\n"
    "sec_part_types\n"
    "    0 1001\n"
    "sec_part_zaids\n"
    "    92000 92235.proton\n"
    "e_bounds_0\n"
    "    20 10 5 1e-11\n"
    "e_bounds_1001\n"
    "    20 10 1e-11\n"
    "pn_prod_full_0\n"
    "    0\n"
    "    1 0 0 0 1\n"
    "    0 0 0 1 0\n"
    "    1 0 1 0 0\n"
    "    0 1 0 0 0\n"
    "    1\n"
    "    1\n"
    "    0 0 1 0 1\n"
    "    0 1 0 0 0\n"
    "    1 0 0 0 1\n"
    "    0 1 0 1 0\n"
    "    0\n"
    "pn_prod_full_1001\n"
    "    0\n"
    "    1 0 0 1 1\n"
    "    0 0 1 1 0\n"
    "    0 1 1 0\n"
    "    1\n"
    "    0 1 1 0 0\n"
    "    1 1 0 0 1\n"
    "    1 0 0 1\n"
    "heating_0\n"
    "    21 11 5.1 3 4\n"
    "    6 7\n"
    "heating_1001\n"
    "    25 15 9.1 7 8\n"
    "    10 11\n"
    "kerma_0\n"
    "    210 110 51 30 40\n"
    "    60 70\n"
    "kerma_1001\n"
    "    250 150 91 70 80\n"
    "    100 110\n"
    "end\n"
  );

  return (header_str + "\n" + zaid_str1 + table_str 
                     + "\n" + zaid_str2 + table_str
                     + "\n" + zaid_str3 + table_str);
}

void verifyChunk( const MultigroupLibrary& chunk ) {
  std::string header( 
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.\n"
    "Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\n"
    "Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.\n"
    "Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.\n"
  );

  CHECK( chunk.numberTables() == 3 );
  CHECK( std::is_same_v< decltype(chunk.tables()), const std::vector<MultigroupTable>& > );
  CHECK( chunk.hasTable("test_zaid_1") );
  CHECK( chunk.hasTable("test_zaid_2") );
  CHECK( chunk.hasTable("test_zaid_3") );
  CHECK( not chunk.hasTable("asdf") );
  CHECK( chunk.header() == header );
}

void verifySubChunk( const MultigroupTable& chunk ) {
  // metadata
  CHECK( "this is some information for the table" == chunk.metadata().information() );
  CHECK( "mendf71x" == chunk.metadata().libraryName() );
  CHECK( "12/22/2011" == chunk.metadata().sourceDate() );
  CHECK( "08/07/2013" == chunk.metadata().processingDate() );
  CHECK_THAT( 233.0248, WithinRel( chunk.metadata().atomicWeightRatio().value() ) );
  CHECK_THAT( 235.043937521619, WithinRel( chunk.metadata().atomicWeight().value() ) );
  CHECK_THAT( 2.53e-8, WithinRel( chunk.metadata().temperature().value() ) );
  CHECK_THAT( 1e+10, WithinRel( chunk.metadata().dilution().value() ) );
  CHECK( 7 == chunk.metadata().numberGroups() );
  CHECK( 2 == chunk.metadata().numberReactions() );
  CHECK( 2 == chunk.metadata().numberOutgoingParticles() );
  CHECK( 2 == chunk.metadata().numberLegendreMoments() );
  CHECK( 2 == chunk.metadata().numberOutgoingLegendreMoments( 0 ) );
  CHECK( 2 == chunk.metadata().numberOutgoingLegendreMoments( 1001 ) );

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

  // the scattering matrix
  CHECK( "pn_full" == chunk.scatteringMatrix().keyword() );
  CHECK( false == chunk.scatteringMatrix().empty() );
  CHECK( 100 == chunk.scatteringMatrix().size() );
  CHECK( 7 == chunk.scatteringMatrix().numberPrimaryGroups() );
  CHECK( 7 == chunk.scatteringMatrix().numberOutgoingGroups() );
  CHECK( 2 == chunk.scatteringMatrix().numberLegendreMoments() );
  auto moment = chunk.scatteringMatrix().moment( 0 );
  CHECK( 7 == moment.matrix().size() );
  CHECK( 7 == moment.matrix()[0].size() );
  CHECK( 0 == moment.order() );
  CHECK_THAT( 0.999999999999, WithinRel( moment.matrix()[0][0] ) );
  CHECK_THAT( 1e-13, WithinRel( moment.matrix()[0][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][3] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][4] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][5] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][6] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][0] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[1][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][3] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][4] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][5] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][6] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][1] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[2][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][3] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][4] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][5] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][6] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][2] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[3][3] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][4] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][5] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][6] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][3] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[4][4] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][5] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][6] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][3] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][4] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[5][5] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][6] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][3] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][4] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][5] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[6][6] ) );
  moment = chunk.scatteringMatrix().moment( 1 );
  CHECK( 7 == moment.matrix().size() );
  CHECK( 7 == moment.matrix()[0].size() );
  CHECK( 1 == moment.order() );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][3] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][4] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][5] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[0][6] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][3] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][4] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[1][5] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][6] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][3] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[2][4] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][5] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][6] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][2] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[3][3] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][4] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][5] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][6] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][1] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[4][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][3] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][4] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][5] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][6] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][0] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[5][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][3] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][4] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][5] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][6] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[6][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][3] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][4] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][5] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][6] ) );

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

  // principal heating numbers
  auto heating = chunk.primaryHeatingNumbers();
  CHECK( "heating" == heating.keyword() );
  CHECK( std::nullopt == heating.particle() );
  CHECK( false == heating.empty() );
  CHECK( 7 == heating.size() );
  CHECK( 7 == heating.values().size() );
  CHECK( 7 == heating.numberGroups() );
  CHECK_THAT( 11, WithinRel( heating.values()[0] ) );
  CHECK_THAT( 22, WithinRel( heating.values()[1] ) );
  CHECK_THAT( 33, WithinRel( heating.values()[2] ) );
  CHECK_THAT( 44, WithinRel( heating.values()[3] ) );
  CHECK_THAT( 55, WithinRel( heating.values()[4] ) );
  CHECK_THAT( 66, WithinRel( heating.values()[5] ) );
  CHECK_THAT( 77, WithinRel( heating.values()[6] ) );

  // principal kerma
  auto kerma = chunk.primaryKerma();
  CHECK( "kerma" == kerma.keyword() );
  CHECK( std::nullopt == kerma.particle() );
  CHECK( false == kerma.empty() );
  CHECK( 7 == kerma.size() );
  CHECK( 7 == kerma.values().size() );
  CHECK( 7 == kerma.numberGroups() );
  CHECK_THAT( 110, WithinRel( kerma.values()[0] ) );
  CHECK_THAT( 220, WithinRel( kerma.values()[1] ) );
  CHECK_THAT( 330, WithinRel( kerma.values()[2] ) );
  CHECK_THAT( 440, WithinRel( kerma.values()[3] ) );
  CHECK_THAT( 550, WithinRel( kerma.values()[4] ) );
  CHECK_THAT( 660, WithinRel( kerma.values()[5] ) );
  CHECK_THAT( 770, WithinRel( kerma.values()[6] ) );

  // outgoing particle types
  auto types = chunk.outgoingParticleTypes();
  CHECK( "sec_part_types" == types.keyword() );
  CHECK( false == types.empty() );
  CHECK( 2 == types.size() );
  CHECK( 2 == types.values().size() );
  CHECK( 2 == types.numberOutgoingParticles() );
  CHECK(    0 == types.values()[0] );
  CHECK( 1001 == types.values()[1] );

  // outgoing particle transport data
  auto transport = chunk.outgoingParticleTransportData();
  CHECK( "sec_part_zaids" == transport.keyword() );
  CHECK( false == transport.empty() );
  CHECK( 2 == transport.size() );
  CHECK( 2 == transport.values().size() );
  CHECK( 2 == transport.numberOutgoingParticles() );
  CHECK( "92000" == transport.values()[0] );
  CHECK( "92235.proton" == transport.values()[1] );

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

  // the outgoing production matrix: 0
  auto production = chunk.outgoingProductionMatrix( 0 );
  CHECK( "pn_prod_full_0" == production.keyword() );
  CHECK( 0 == production.particle() );
  CHECK( false == production.empty() );
  CHECK( 44 == production.size() );
  CHECK( 7 == production.numberPrimaryGroups() );
  CHECK( 3 == production.numberOutgoingGroups() );
  CHECK( 2 == production.numberLegendreMoments() );
  moment = production.moment( 0 );
  CHECK( 7 == moment.matrix().size() );
  CHECK( 3 == moment.matrix()[0].size() );
  CHECK( 0 == moment.order() );
  CHECK_THAT( 1, WithinRel( moment.matrix()[0][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][0] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[1][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][1] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[2][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][0] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[3][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][2] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[4][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][0] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[5][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][1] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[6][2] ) );
  moment = production.moment( 1 );
  CHECK( 7 == moment.matrix().size() );
  CHECK( 3 == moment.matrix()[0].size() );
  CHECK( 1 == moment.order() );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][1] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[0][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][0] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[1][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][2] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[2][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][0] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[3][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][1] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[4][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][0] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[5][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][2] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[6][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][2] ) );

  // the outgoing production matrix: 1001
  production = chunk.outgoingProductionMatrix( 1001 );
  CHECK( "pn_prod_full_1001" == production.keyword() );
  CHECK( 1001 == production.particle() );
  CHECK( false == production.empty() );
  CHECK( 30 == production.size() );
  CHECK( 7 == production.numberPrimaryGroups() );
  CHECK( 2 == production.numberOutgoingGroups() );
  CHECK( 2 == production.numberLegendreMoments() );
  moment = production.moment( 0 );
  CHECK( 7 == moment.matrix().size() );
  CHECK( 2 == moment.matrix()[0].size() );
  CHECK( 0 == moment.order() );
  CHECK_THAT( 1, WithinRel( moment.matrix()[0][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][0] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[1][1] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[2][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][0] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[3][1] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[4][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][0] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[5][1] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[6][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][1] ) );
  moment = production.moment( 1 );
  CHECK( 7 == moment.matrix().size() );
  CHECK( 2 == moment.matrix()[0].size() );
  CHECK( 1 == moment.order() );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][0] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[0][1] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[1][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][0] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[2][1] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[3][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][0] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[4][1] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[5][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][0] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[6][1] ) );

  // outgoing heating numbers: 0
  heating = chunk.outgoingHeatingNumbers( 0 );
  CHECK( "heating_0" == heating.keyword() );
  CHECK( 0 == heating.particle() );
  CHECK( false == heating.empty() );
  CHECK( 7 == heating.size() );
  CHECK( 7 == heating.values().size() );
  CHECK( 7 == heating.numberGroups() );
  CHECK_THAT(  21, WithinRel( heating.values()[0] ) );
  CHECK_THAT(  11, WithinRel( heating.values()[1] ) );
  CHECK_THAT( 5.1, WithinRel( heating.values()[2] ) );
  CHECK_THAT(   3, WithinRel( heating.values()[3] ) );
  CHECK_THAT(   4, WithinRel( heating.values()[4] ) );
  CHECK_THAT(   6, WithinRel( heating.values()[5] ) );
  CHECK_THAT(   7, WithinRel( heating.values()[6] ) );

  // outgoing heating numbers: 1001
  heating = chunk.outgoingHeatingNumbers( 1001 );
  CHECK( "heating_1001" == heating.keyword() );
  CHECK( 1001 == heating.particle() );
  CHECK( false == heating.empty() );
  CHECK( 7 == heating.size() );
  CHECK( 7 == heating.values().size() );
  CHECK( 7 == heating.numberGroups() );
  CHECK_THAT(  25, WithinRel( heating.values()[0] ) );
  CHECK_THAT(  15, WithinRel( heating.values()[1] ) );
  CHECK_THAT( 9.1, WithinRel( heating.values()[2] ) );
  CHECK_THAT(   7, WithinRel( heating.values()[3] ) );
  CHECK_THAT(   8, WithinRel( heating.values()[4] ) );
  CHECK_THAT(  10, WithinRel( heating.values()[5] ) );
  CHECK_THAT(  11, WithinRel( heating.values()[6] ) );

  // outgoing kerma: 0
  kerma = chunk.outgoingKerma( 0 );
  CHECK( "kerma_0" == kerma.keyword() );
  CHECK( 0 == kerma.particle() );
  CHECK( false == kerma.empty() );
  CHECK( 7 == kerma.size() );
  CHECK( 7 == kerma.values().size() );
  CHECK( 7 == kerma.numberGroups() );
  CHECK_THAT(  210, WithinRel( kerma.values()[0] ) );
  CHECK_THAT(  110, WithinRel( kerma.values()[1] ) );
  CHECK_THAT(   51, WithinRel( kerma.values()[2] ) );
  CHECK_THAT(   30, WithinRel( kerma.values()[3] ) );
  CHECK_THAT(   40, WithinRel( kerma.values()[4] ) );
  CHECK_THAT(   60, WithinRel( kerma.values()[5] ) );
  CHECK_THAT(   70, WithinRel( kerma.values()[6] ) );

  // outgoing kerma: 1001
  kerma = chunk.outgoingKerma( 1001 );
  CHECK( "kerma_1001" == kerma.keyword() );
  CHECK( 1001 == kerma.particle() );
  CHECK( false == kerma.empty() );
  CHECK( 7 == kerma.size() );
  CHECK( 7 == kerma.values().size() );
  CHECK( 7 == kerma.numberGroups() );
  CHECK_THAT(  250, WithinRel( kerma.values()[0] ) );
  CHECK_THAT(  150, WithinRel( kerma.values()[1] ) );
  CHECK_THAT(   91, WithinRel( kerma.values()[2] ) );
  CHECK_THAT(   70, WithinRel( kerma.values()[3] ) );
  CHECK_THAT(   80, WithinRel( kerma.values()[4] ) );
  CHECK_THAT(  100, WithinRel( kerma.values()[5] ) );
  CHECK_THAT(  110, WithinRel( kerma.values()[6] ) );
}