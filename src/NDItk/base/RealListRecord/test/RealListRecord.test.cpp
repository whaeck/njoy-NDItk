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

std::string chunk();
void verifyChunk( const RealListRecord& );

SCENARIO( "RealListRecord" ) {

  GIVEN( "valid data for a RealListRecord instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      RealListRecord chunk( "e_bounds", { 20., 18., 16., 14., 10., 5, 1, 1e-11 } );

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
      RealListRecord chunk( "e_bounds" );
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
         "                  20                  18                  16                  14\n"
         "                  10                   5                   1               1e-11\n";
}

void verifyChunk( const RealListRecord& chunk ) {

  CHECK( "e_bounds" == chunk.keyword() );
  CHECK( true == chunk.hasContent() );
  CHECK( 8 == chunk.content().value().size() );
  CHECK_THAT(    20, WithinRel( chunk.content().value()[0] ) );
  CHECK_THAT(    18, WithinRel( chunk.content().value()[1] ) );
  CHECK_THAT(    16, WithinRel( chunk.content().value()[2] ) );
  CHECK_THAT(    14, WithinRel( chunk.content().value()[3] ) );
  CHECK_THAT(    10, WithinRel( chunk.content().value()[4] ) );
  CHECK_THAT(     5, WithinRel( chunk.content().value()[5] ) );
  CHECK_THAT(     1, WithinRel( chunk.content().value()[6] ) );
  CHECK_THAT( 1e-11, WithinRel( chunk.content().value()[7] ) );
}
