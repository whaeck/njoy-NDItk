// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/base/SingleRealRecord.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using SingleRealRecord = base::SingleRealRecord;

std::string chunk();
void verifyChunk( const SingleRealRecord& );

SCENARIO( "SingleRealRecord" ) {

  GIVEN( "valid data for a SingleRealRecord instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      SingleRealRecord chunk( "temp", 2.53e-8 );

      THEN( "a SingleRealRecord can be constructed and members can "
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

    WHEN( "the data is defined by iterators" ) {

      auto iter = record.begin() + 4;
      auto end = record.end();
      SingleRealRecord chunk( "temp" );
      chunk.read( iter, end );

      THEN( "a SingleRealRecord can be constructed and members can "
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

  return "temp\n"
         "            2.53e-08\n";
}

void verifyChunk( const SingleRealRecord& chunk ) {

  CHECK( "temp" == chunk.keyword() );
  CHECK_THAT( 2.53e-8, WithinRel( chunk.content().value() ) );
}
