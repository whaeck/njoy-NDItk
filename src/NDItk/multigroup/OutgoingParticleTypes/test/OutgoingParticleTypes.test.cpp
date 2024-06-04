// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/multigroup/OutgoingParticleTypes.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using OutgoingParticleTypes = multigroup::OutgoingParticleTypes;

std::string chunk();
void verifyChunk( const OutgoingParticleTypes& );
std::string chunkWithInsufficientNumberValues();

SCENARIO( "OutgoingParticleTypes" ) {

  GIVEN( "valid data for an OutgoingParticleTypes instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< int > values = { 0, 1001 };

      OutgoingParticleTypes chunk( std::move( values ) );

      THEN( "an OutgoingParticleTypes can be constructed and members can "
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

      OutgoingParticleTypes chunk;
      chunk.read( iter, end, 2 );

      THEN( "an OutgoingParticleTypes can be constructed and members can "
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

  GIVEN( "invalid data for an OutgoingParticleTypes instance" ) {

    WHEN( "the number of particle types is insufficient" ) {

      THEN( "an exception is thrown" ) {

        std::vector< int > empty = {};

        CHECK_THROWS( OutgoingParticleTypes( std::move( empty ) ) );
      } // THEN
    } // WHEN

    WHEN( "reading the data of the record and the number of "
          "values is insufficient" ) {

      std::string record = chunkWithInsufficientNumberValues();
      auto iter = record.begin() + 14;
      auto end = record.end();
      OutgoingParticleTypes chunk;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( chunk.read( iter, end, 0 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return "sec_part_types\n"
         "    0 1001\n";
}

void verifyChunk( const OutgoingParticleTypes& chunk ) {

  CHECK( "sec_part_types" == chunk.keyword() );
  CHECK(    0 == chunk.values()[0] );
  CHECK( 1001 == chunk.values()[1] );

  CHECK( false == chunk.empty() );
  CHECK( 2 == chunk.size() );

  CHECK( 2 == chunk.numberOutgoingParticles() );
}

std::string chunkWithInsufficientNumberValues() {

  return "sec_part_types\n";
}
