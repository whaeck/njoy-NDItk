// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/base/ColumnData.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;

template<typename T, size_t n>
using ColumnData = base::ColumnData<T, n>;

std::string chunk();

void verifyChunk( const ColumnData<int,3>& );

SCENARIO( "ColumnData" ) {

  GIVEN( "valid data for a ColumnData instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      ColumnData<int, 3> chunk( std::vector<int>{1,2,3,4,5,6,7,8,9,10,11,12} );

      THEN( "a ColumnData can be constructed and members can "
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

      auto vals = std::vector<int>{1,2,3,4,5,6,7,8,9,10,11,12};

      ColumnData<int, 3> chunk( vals.begin(), vals.end() );

      THEN( "a ColumnData can be constructed and members can "
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

  return "  1 2 3 \n"
         "  4 5 6 \n"
         "  7 8 9 \n"
         "  10 11 12 \n";
}

void verifyChunk( const ColumnData<int,3>& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 12 == chunk.size() );
  CHECK( 12 == chunk.values().size() );
  CHECK( 3 == chunk.numberColumns() );
  CHECK( 4 == chunk.numberRows() );

  CHECK( 1 == chunk.getColumn(0)[0] );
  CHECK( 4 == chunk.getColumn(0)[1] );
  CHECK( 7 == chunk.getColumn(0)[2] );
  CHECK( 10 == chunk.getColumn(0)[3] );

  CHECK( 2 == chunk.getColumn(1)[0] );
  CHECK( 5 == chunk.getColumn(1)[1] );
  CHECK( 8 == chunk.getColumn(1)[2] );
  CHECK( 11 == chunk.getColumn(1)[3] );

  CHECK( 3 == chunk.getColumn(2)[0] );
  CHECK( 6 == chunk.getColumn(2)[1] );
  CHECK( 9 == chunk.getColumn(2)[2] );
  CHECK( 12 == chunk.getColumn(2)[3] );
}
