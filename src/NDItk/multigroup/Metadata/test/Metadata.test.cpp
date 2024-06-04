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

      std::string zaid = "92235.711nm";
      std::string name = "mendf71x";
      std::optional< std::string > information = "this is some information for the table";
      std::optional< std::string > source = "12/22/2011";
      std::string process = "08/07/2013";
      double awr = 233.0248;
      double weight = 235.043937521619;
      double temperature = 2.53e-8;
      double dilution = 1e+10;
      unsigned int groups = 618;
      std::map< unsigned int, unsigned int > outgoing = { { 0, 30 }, { 1001, 250 } };
      int legendre = 5;
      int upscatter = 3;
      int downscatter = 2;
      unsigned int reactions = 7;

      Metadata chunk( std::move( zaid ), std::move( name ),
                      std::move( process ),
                      awr, temperature, dilution,
                      groups, outgoing, reactions, legendre,
                      std::move( information ),
                      std::move( source ),
                      weight,
                      upscatter, downscatter );

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

    WHEN( "the data is read using iterators" ) {

      auto iter = record.begin();
      auto end = record.end();

      auto readKey = [] ( auto&& iter, auto&& end ) {

        return njoy::tools::disco::FreeFormatCharacter::read< std::string >( iter, end );
      };

      Metadata chunk;
      chunk.read( readKey( iter, end ), iter, end );
      chunk.read( readKey( iter, end ), iter, end );
      chunk.read( readKey( iter, end ), iter, end );
      chunk.read( readKey( iter, end ), iter, end );
      chunk.read( readKey( iter, end ), iter, end );
      chunk.read( readKey( iter, end ), iter, end );
      chunk.read( readKey( iter, end ), iter, end );
      chunk.read( readKey( iter, end ), iter, end );
      chunk.read( readKey( iter, end ), iter, end );
      chunk.read( readKey( iter, end ), iter, end );
      chunk.read( readKey( iter, end ), iter, end );
      chunk.read( readKey( iter, end ), iter, end );
      chunk.read( readKey( iter, end ), iter, end );
      chunk.read( readKey( iter, end ), iter, end );
      chunk.read( readKey( iter, end ), iter, end );
      chunk.read( readKey( iter, end ), iter, end );
      chunk.read( readKey( iter, end ), iter, end );

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

  return "zaid\n"
         "    92235.711nm\n"
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
         "    618\n"
         "num_reac\n"
         "    7\n"
         "pn_order\n"
         "    5\n"
         "up_grps\n"
         "    3\n"
         "down_grps\n"
         "    2\n"
         "num_sec_parts\n"
         "    2\n"
         "num_grps_0\n"
         "    30\n"
         "num_grps_1001\n"
         "    250\n";
}

void verifyChunk( const Metadata& chunk ) {

  CHECK( "92235.711nm" == chunk.zaid() );
  CHECK( "this is some information for the table" == chunk.information() );
  CHECK( "mendf71x" == chunk.libraryName() );
  CHECK( "12/22/2011" == chunk.sourceDate() );
  CHECK( "08/07/2013" == chunk.processingDate() );
  CHECK_THAT( 233.0248, WithinRel( chunk.atomicWeightRatio().value() ) );
  CHECK_THAT( 235.043937521619, WithinRel( chunk.atomicWeight().value() ) );
  CHECK_THAT( 2.53e-8, WithinRel( chunk.temperature().value() ) );
  CHECK_THAT( 1e+10, WithinRel( chunk.dilution().value() ) );
  CHECK( 618 == chunk.numberGroups() );
  CHECK(  30 == chunk.numberOutgoingGroups( 0 ) );
  CHECK( 250 == chunk.numberOutgoingGroups( 1001 ) );
  CHECK(   2 == chunk.numberOutgoingParticles() );
  CHECK(   3 == chunk.numberUpscatterGroups() );
  CHECK(   2 == chunk.numberDownscatterGroups() );
  CHECK(   7 == chunk.numberReactions() );
  CHECK(   5 == chunk.numberLegendreMoments() );

  CHECK_THROWS( chunk.numberOutgoingGroups( 1 ) );
}
