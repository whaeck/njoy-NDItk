// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "NDItk/base/SingleStringRecord.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using SingleStringRecord = base::SingleStringRecord;

std::string chunk();
void verifyChunk( const SingleStringRecord& );

SCENARIO( "SingleStringRecord" ) {

  GIVEN( "valid data for a SingleStringRecord instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      SingleStringRecord chunk( "zaid", "92235.711nm" );

      THEN( "a SingleStringRecord can be constructed and members can "
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
      SingleStringRecord chunk( "zaid" );
      chunk.read( iter, end );

      THEN( "a SingleStringRecord can be constructed and members can "
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
         "    92235.711nm\n";
}

void verifyChunk( const SingleStringRecord& chunk ) {

  CHECK( "zaid" == chunk.keyword() );
  CHECK( "92235.711nm" == chunk.content().value() );
}
