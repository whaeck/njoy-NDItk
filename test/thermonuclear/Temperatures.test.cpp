// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/thermonuclear/Temperatures.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using Temperatures = thermonuclear::Temperatures;

std::string chunk();
void verifyChunk( const Temperatures& );
std::string chunkWithInsufficientNumberValues();

SCENARIO( "Temperatures" ) {

  GIVEN( "valid data for a Temperatures instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > values = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7 };

      Temperatures chunk( std::move( values ) );

      THEN( "a Temperatures can be constructed and members can "
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

      auto iter = record.begin() + 5;
      auto end = record.end();

      Temperatures chunk;
      chunk.read( iter, end, 7 );

      THEN( "a Temperatures can be constructed and members can "
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


  GIVEN( "invalid data for a Temperatures instance" ) {

    WHEN( "the number of boundary values is insufficient" ) {

      THEN( "an exception is thrown" ) {

        std::vector< double > empty = {};

        CHECK_THROWS( Temperatures( std::move( empty ) ) );
      } // THEN
    } // WHEN

    WHEN( "reading the data of the record and the number of boundary "
          "values is insufficient" ) {

      std::string record = chunkWithInsufficientNumberValues();
      auto iter = record.begin() + 5;
      auto end = record.end();
      Temperatures chunk;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( chunk.read( iter, end, 0 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return "temps\n"
         "    0.1 0.2 0.3 0.4 0.5\n"
         "    0.6 0.7\n";
}

void verifyChunk( const Temperatures& chunk ) {

  CHECK( "temps" == chunk.keyword() );
  CHECK( false == chunk.empty() );
  CHECK( 7 == chunk.size() );
  CHECK( 7 == chunk.values().size() );
  CHECK( 7 == chunk.numberTemperatures() );
  CHECK_THAT( 0.1, WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 0.2, WithinRel( chunk.values()[1] ) );
  CHECK_THAT( 0.3, WithinRel( chunk.values()[2] ) );
  CHECK_THAT( 0.4, WithinRel( chunk.values()[3] ) );
  CHECK_THAT( 0.5, WithinRel( chunk.values()[4] ) );
  CHECK_THAT( 0.6, WithinRel( chunk.values()[5] ) );
  CHECK_THAT( 0.7, WithinRel( chunk.values()[6] ) );
}
std::string chunkWithInsufficientNumberValues() {

  return "temps\n";
}
