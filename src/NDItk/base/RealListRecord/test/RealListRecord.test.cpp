// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/base/RealListRecord.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using RealListRecord = base::RealListRecord;
using Keyword = base::Keyword;

std::string chunk();
void verifyChunk( const RealListRecord& );

SCENARIO( "RealListRecord" ) {

  GIVEN( "valid data for a RealListRecord instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      RealListRecord chunk( Keyword( "e_bounds" ), { 20.000001, 18.000000001, 16.0000000000001, 14., 10., 5, 1, 1e-11 } );

      THEN( "a RealListRecord can be constructed and members can "
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
      RealListRecord chunk( Keyword( "e_bounds" ) );
      chunk.read( iter, end, 8 );

      THEN( "a RealListRecord can be constructed and members can "
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
         "    20.000001 18.000000001 16.0000000000001 14 10\n"
         "    5 1 1e-11\n";
}

void verifyChunk( const RealListRecord& chunk ) {

  CHECK( "e_bounds" == chunk.keyword() );
  CHECK( false == chunk.empty() );
  CHECK( 8 == chunk.size() );
  CHECK( 8 == chunk.values().size() );
  CHECK_THAT(    20.000001, WithinRel( chunk.values()[0] ) );
  CHECK_THAT(    18.000000001, WithinRel( chunk.values()[1] ) );
  CHECK_THAT(    16.0000000000001, WithinRel( chunk.values()[2] ) );
  CHECK_THAT(    14, WithinRel( chunk.values()[3] ) );
  CHECK_THAT(    10, WithinRel( chunk.values()[4] ) );
  CHECK_THAT(     5, WithinRel( chunk.values()[5] ) );
  CHECK_THAT(     1, WithinRel( chunk.values()[6] ) );
  CHECK_THAT( 1e-11, WithinRel( chunk.values()[7] ) );
}
