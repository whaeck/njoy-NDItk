// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/multigroup/TotalCrossSection.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using TotalCrossSection = multigroup::TotalCrossSection;

std::string chunk();
void verifyChunk( const TotalCrossSection& );
std::string chunkWithInsufficientNumberValues();

SCENARIO( "TotalCrossSection" ) {

  GIVEN( "valid data for a TotalCrossSection instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > weights = { 0.1, 0.2, 0.25, 0.05, 0.15, 0.04, 0.06 };

      TotalCrossSection chunk( std::move( weights ) );

      THEN( "a TotalCrossSection can be constructed and members can "
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

      auto iter = record.begin() + 8;
      auto end = record.end();

      TotalCrossSection chunk;
      chunk.read( iter, end, 7 );

      THEN( "a TotalCrossSection can be constructed and members can "
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

  GIVEN( "invalid data for a TotalCrossSection instance" ) {

    WHEN( "the number of weight values is insufficient" ) {

      THEN( "an exception is thrown" ) {

        std::vector< double > empty = {};

        CHECK_THROWS( TotalCrossSection( std::move( empty ) ) );
      } // THEN
    } // WHEN

    WHEN( "reading the data of the record and the number of "
          "values is insufficient" ) {

      std::string record = chunkWithInsufficientNumberValues();
      auto iter = record.begin() + 8;
      auto end = record.end();
      TotalCrossSection chunk;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( chunk.read( iter, end, 0 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return "sig_tot\n"
         "    0.1 0.2 0.25 0.05 0.15\n"
         "    0.04 0.06\n";
}

void verifyChunk( const TotalCrossSection& chunk ) {

  CHECK( "sig_tot" == chunk.keyword() );
  CHECK_THAT( 0.10, WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 0.20, WithinRel( chunk.values()[1] ) );
  CHECK_THAT( 0.25, WithinRel( chunk.values()[2] ) );
  CHECK_THAT( 0.05, WithinRel( chunk.values()[3] ) );
  CHECK_THAT( 0.15, WithinRel( chunk.values()[4] ) );
  CHECK_THAT( 0.04, WithinRel( chunk.values()[5] ) );
  CHECK_THAT( 0.06, WithinRel( chunk.values()[6] ) );

  CHECK( false == chunk.empty() );
  CHECK( 7 == chunk.size() );

  CHECK( 7 == chunk.numberGroups() );
}

std::string chunkWithInsufficientNumberValues() {

  return "sig_tot\n";
}
