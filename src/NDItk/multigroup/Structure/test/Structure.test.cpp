// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/multigroup/Structure.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using Structure = multigroup::Structure;

std::string chunk();
void verifyChunk( const Structure& );

SCENARIO( "Structure" ) {

  GIVEN( "valid data for a Structure instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > boundaries = { 20., 18., 16., 14., 10., 5, 1, 1e-11 };

      Structure chunk( std::move( boundaries ) );

      THEN( "a Structure can be constructed and members can "
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

      Structure chunk;
      chunk.read( iter, end, 8 );

      THEN( "a Structure can be constructed and members can "
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

  return "e_bounds\n"
         "                  20                  18                  16                  14\n"
         "                  10                   5                   1               1e-11\n";
}

void verifyChunk( const Structure& chunk ) {

  CHECK( "e_bounds" == chunk.keyword() );
  CHECK( 8 == chunk.boundaries().value().size() );
}
