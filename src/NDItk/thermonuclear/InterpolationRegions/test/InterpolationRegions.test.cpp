// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/thermonuclear/InterpolationRegions.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using InterpolationRegions = thermonuclear::InterpolationRegions;

std::string chunk();
std::vector< int > data();
void verifyChunk( const InterpolationRegions& );
std::vector< int > dataWithInsufficientLength();

SCENARIO( "InterpolationRegions" ) {

  GIVEN( "valid data for an InterpolationRegions instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< int > endIndices  = { 3, 6, 9, 12, 15 };
      std::vector< int > interpTypes = { 1, 2, 3, 4, 5 };

      InterpolationRegions chunk( endIndices, interpTypes );

      THEN( "an InterpolationRegions can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "the record can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output );

        CHECK( buffer == record );
      } // THEN
    } // WHEN

    WHEN( "the data is defined using iterators" ) {

      std::vector< int > values = data();
      auto begin = values.begin();
      auto end = values.end();

      InterpolationRegions chunk( begin, end );

      THEN( "a InterpolationRegions can be constructed and members can "
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

  GIVEN( "invalid data for a InterpolationRegions instance" ) {

    WHEN( "the number of indices and interpolation types is insufficient" ) {

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( InterpolationRegions( { 3, 6 }, { 1 } ) );
      } // THEN
    } // WHEN

    WHEN( "using iterators and the number of data values are "
          "insufficient" ) {

      std::vector< int > values = dataWithInsufficientLength();
      auto begin = values.begin();
      auto end = values.end();

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( InterpolationRegions( begin, end ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return "  5\n"
         "  3  1\n"
         "  6  2\n"
         "  9  3\n"
         "  12  4\n"
         "  15  5\n";
}

std::vector< int > data() {

  return { 5, 3,1, 6,2, 9,3, 12,4, 15,5 };
}

void verifyChunk( const InterpolationRegions& chunk ) {

  CHECK( 5 == chunk.numberRegions() );
  CHECK( 15 == chunk.totalSize() );

  CHECK( 1 == chunk.regionBeginIndex(0) );
  CHECK( 3 == chunk.regionEndIndex(0) );
  CHECK( 3 == chunk.regionSize(0) );
  CHECK( 1 == chunk.regionInterpolationType(0) );

  CHECK( 4 == chunk.regionBeginIndex(1) );
  CHECK( 6 == chunk.regionEndIndex(1) );
  CHECK( 3 == chunk.regionSize(1) );
  CHECK( 2 == chunk.regionInterpolationType(1) );

  CHECK( 7 == chunk.regionBeginIndex(2) );
  CHECK( 9 == chunk.regionEndIndex(2) );
  CHECK( 3 == chunk.regionSize(2) );
  CHECK( 3 == chunk.regionInterpolationType(2) );

  CHECK( 10 == chunk.regionBeginIndex(3) );
  CHECK( 12 == chunk.regionEndIndex(3) );
  CHECK( 3 == chunk.regionSize(3) );
  CHECK( 4 == chunk.regionInterpolationType(3) );

  CHECK( 13 == chunk.regionBeginIndex(4) );
  CHECK( 15 == chunk.regionEndIndex(4) );
  CHECK( 3 == chunk.regionSize(4) );
  CHECK( 5 == chunk.regionInterpolationType(4) );
}

std::vector< int > dataWithInsufficientLength() {

  return { 3 };
}