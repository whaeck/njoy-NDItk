// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "NDItk/base/SingleIntegerRecord.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using SingleIntegerRecord = base::SingleIntegerRecord;
using Keyword = base::Keyword;

std::string chunk();
void verifyChunk( const SingleIntegerRecord& );

SCENARIO( "SingleIntegerRecord" ) {

  GIVEN( "valid data for a SingleIntegerRecord instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      SingleIntegerRecord chunk( Keyword( "num_grps" ), 618 );

      THEN( "a SingleIntegerRecord can be constructed and members can "
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

      auto iter = record.begin() + 8;
      auto end = record.end();
      SingleIntegerRecord chunk( Keyword( "num_grps" ) );
      chunk.read( iter, end );

      THEN( "a SingleIntegerRecord can be constructed and members can "
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

  return "num_grps\n"
         "    618\n";
}

void verifyChunk( const SingleIntegerRecord& chunk ) {

  CHECK( "num_grps" == chunk.keyword() );
  CHECK( false == chunk.empty() );
  CHECK( 618 == chunk.data().value() );
}
