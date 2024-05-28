// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/multigroup/Velocities.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using Velocities = multigroup::Velocities;

std::string chunk();
void verifyChunk( const Velocities& );
std::string chunkWithInsufficientNumberValues();

SCENARIO( "Velocities" ) {

  GIVEN( "valid data for a Velocities instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > velocities = { 0.1, 0.2, 0.25, 0.05, 0.15, 0.04, 0.06 };

      Velocities chunk( std::move( velocities ) );

      THEN( "a Velocities can be constructed and members can "
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

      auto iter = record.begin() + 3;
      auto end = record.end();

      Velocities chunk;
      chunk.read( iter, end, 7 );

      THEN( "a Velocities can be constructed and members can "
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

  GIVEN( "invalid data for a Velocities instance" ) {

    WHEN( "the number of weight values is insufficient" ) {

      THEN( "an exception is thrown" ) {

        std::vector< double > empty = {};

        CHECK_THROWS( Velocities( std::move( empty ) ) );
      } // THEN
    } // WHEN

    WHEN( "reading the data of the record and the number of "
          "values is insufficient" ) {

      std::string record = chunkWithInsufficientNumberValues();
      auto iter = record.begin() + 3;
      auto end = record.end();
      Velocities chunk;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( chunk.read( iter, end, 0 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return "vel\n"
         "    0.1 0.2 0.25 0.05 0.15\n"
         "    0.04 0.06\n";
}

void verifyChunk( const Velocities& chunk ) {

  CHECK( "vel" == chunk.keyword() );
  CHECK_THAT( 0.10, WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 0.20, WithinRel( chunk.values()[1] ) );
  CHECK_THAT( 0.25, WithinRel( chunk.values()[2] ) );
  CHECK_THAT( 0.05, WithinRel( chunk.values()[3] ) );
  CHECK_THAT( 0.15, WithinRel( chunk.values()[4] ) );
  CHECK_THAT( 0.04, WithinRel( chunk.values()[5] ) );
  CHECK_THAT( 0.06, WithinRel( chunk.values()[6] ) );

  CHECK( false == chunk.empty() );
  CHECK( 7 == chunk.size() );

  CHECK( 7 == chunk.numberGroups() );
}

std::string chunkWithInsufficientNumberValues() {

  return "vel\n";
}
