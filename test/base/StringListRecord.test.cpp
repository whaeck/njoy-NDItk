// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/base/StringListRecord.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using StringListRecord = base::StringListRecord;
using Keyword = base::Keyword;

std::string chunk();
void verifyChunk( const StringListRecord& );

SCENARIO( "StringListRecord" ) {

  GIVEN( "valid data for a StringListRecord instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      StringListRecord chunk( Keyword( "sec_part_zaids" ),
                              { "1a", "2b", "3c", "4d", "5e",
                                "6f", "7g", "8h" } );

      THEN( "a StringListRecord can be constructed and members can "
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

      auto iter = record.begin() + 14;
      auto end = record.end();
      StringListRecord chunk( Keyword( "sec_part_zaids" ) );
      chunk.read( iter, end, 8 );

      THEN( "a StringListRecord can be constructed and members can "
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

  return "sec_part_zaids\n"
         "    1a 2b 3c 4d 5e\n"
         "    6f 7g 8h\n";
}

void verifyChunk( const StringListRecord& chunk ) {

  CHECK( "sec_part_zaids" == chunk.keyword() );
  CHECK( false == chunk.empty() );
  CHECK( 8 == chunk.size() );
  CHECK( 8 == chunk.values().size() );
  CHECK( "1a" == chunk.values()[0] );
  CHECK( "2b" == chunk.values()[1] );
  CHECK( "3c" == chunk.values()[2] );
  CHECK( "4d" == chunk.values()[3] );
  CHECK( "5e" == chunk.values()[4] );
  CHECK( "6f" == chunk.values()[5] );
  CHECK( "7g" == chunk.values()[6] );
  CHECK( "8h" == chunk.values()[7] );
}
