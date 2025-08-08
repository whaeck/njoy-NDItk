// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/multigroup/OutgoingParticleTransportData.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using OutgoingParticleTransportData = multigroup::OutgoingParticleTransportData;

std::string chunk();
void verifyChunk( const OutgoingParticleTransportData& );
std::string chunkWithInsufficientNumberValues();

SCENARIO( "OutgoingParticleTransportData" ) {

  GIVEN( "valid data for an OutgoingParticleTransportData instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< std::string > values = { "92000", "92235.proton" };

      OutgoingParticleTransportData chunk( std::move( values ) );

      THEN( "an OutgoingParticleTransportData can be constructed and members can "
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

      auto iter = record.begin() + 14;
      auto end = record.end();

      OutgoingParticleTransportData chunk;
      chunk.read( iter, end, 2 );

      THEN( "an OutgoingParticleTransportData can be constructed and members can "
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

  GIVEN( "invalid data for an OutgoingParticleTransportData instance" ) {

    WHEN( "the number of zaid values is insufficient" ) {

      THEN( "an exception is thrown" ) {

        std::vector< std::string > empty = {};

        CHECK_THROWS( OutgoingParticleTransportData( std::move( empty ) ) );
      } // THEN
    } // WHEN

    WHEN( "reading the data of the record and the number of "
          "values is insufficient" ) {

      std::string record = chunkWithInsufficientNumberValues();
      auto iter = record.begin() + 14;
      auto end = record.end();
      OutgoingParticleTransportData chunk;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( chunk.read( iter, end, 0 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return "sec_part_zaids\n"
         "    92000 92235.proton\n";
}

void verifyChunk( const OutgoingParticleTransportData& chunk ) {

  CHECK( "sec_part_zaids" == chunk.keyword() );
  CHECK( "92000" == chunk.values()[0] );
  CHECK( "92235.proton" == chunk.values()[1] );

  CHECK( false == chunk.empty() );
  CHECK( 2 == chunk.size() );

  CHECK( 2 == chunk.numberOutgoingParticles() );
}

std::string chunkWithInsufficientNumberValues() {

  return "sec_part_zaids\n";
}
