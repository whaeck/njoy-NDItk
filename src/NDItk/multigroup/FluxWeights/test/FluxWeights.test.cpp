// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/multigroup/FluxWeights.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using FluxWeights = multigroup::FluxWeights;

std::string chunk();
void verifyChunk( const FluxWeights& );

SCENARIO( "FluxWeights" ) {

  GIVEN( "valid data for a FluxWeights instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > boundaries = { 0.1, 0.2, 0.25, 0.05, 0.15, 0.04, 0.06 };

      FluxWeights chunk( std::move( boundaries ) );

      THEN( "a FluxWeights can be constructed and members can "
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

      auto iter = record.begin() + 8;
      auto end = record.end();

      FluxWeights chunk;
      chunk.read( iter, end, 7 );

      THEN( "a FluxWeights can be constructed and members can "
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

  return "wgts\n"
         "                 0.1                 0.2                0.25                0.05\n"
         "                0.15                0.04                0.06\n";
}

void verifyChunk( const FluxWeights& chunk ) {

  CHECK( "wgts" == chunk.keyword() );
  CHECK( false == chunk.empty() );
  CHECK( 7 == chunk.size() );
  CHECK( 7 == chunk.values().size() );
  CHECK( 7 == chunk.numberGroups() );
  CHECK_THAT( 0.10, WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 0.20, WithinRel( chunk.values()[1] ) );
  CHECK_THAT( 0.25, WithinRel( chunk.values()[2] ) );
  CHECK_THAT( 0.05, WithinRel( chunk.values()[3] ) );
  CHECK_THAT( 0.15, WithinRel( chunk.values()[4] ) );
  CHECK_THAT( 0.04, WithinRel( chunk.values()[5] ) );
  CHECK_THAT( 0.06, WithinRel( chunk.values()[6] ) );
}
