// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "NDItk/base/InformationRecord.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using InformationRecord = base::InformationRecord;

std::string chunk();
void verifyChunk( const InformationRecord& );

SCENARIO( "InformationRecord" ) {

  GIVEN( "valid data for a InformationRecord instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      InformationRecord chunk( "this is some information for the table" );

      THEN( "a InformationRecord can be constructed and members can "
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
      InformationRecord chunk;
      chunk.read( iter, end );

      THEN( "a InformationRecord can be constructed and members can "
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

  return "info\n"
         "    this is some information for the table\n";
}

void verifyChunk( const InformationRecord& chunk ) {

  CHECK( "info" == chunk.keyword() );
  CHECK( false == chunk.empty() );
  CHECK( "this is some information for the table" == chunk.data() );
}
