// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/multigroup/Kerma.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using Kerma = multigroup::Kerma;

std::string chunk();
void verifyChunk( const Kerma& );
std::string chunkWithParticle();
void verifyChunkWithParticle( const Kerma& );
std::string chunkWithInsufficientNumberValues();

SCENARIO( "Kerma" ) {

  GIVEN( "valid data for a primary Kerma instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > values = { 10., 9., 8., 7., 6., 5., 4. };

      Kerma chunk( std::move( values ) );

      THEN( "a Kerma can be constructed and members can "
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

      auto iter = record.begin() + 7;
      auto end = record.end();

      Kerma chunk;
      chunk.read( iter, end, 7 );

      THEN( "a Kerma can be constructed and members can "
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

  GIVEN( "valid data for a outgoing Kerma instance" ) {

    std::string record = chunkWithParticle();

    WHEN( "the data is given explicitly" ) {

      unsigned int particle = 1001;
      std::vector< double > values = { 10., 9., 8., 7., 6., 5., 4. };

      Kerma chunk( particle, std::move( values ) );

      THEN( "a Kerma can be constructed and members can "
            "be tested" ) {

        verifyChunkWithParticle( chunk );
      } // THEN

      THEN( "the record can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output );

        CHECK( buffer == record );
      } // THEN
    } // WHEN

    WHEN( "the data is read using iterators" ) {

      auto iter = record.begin() + 12;
      auto end = record.end();

      Kerma chunk( 1001 );
      chunk.read( iter, end, 7 );

      THEN( "a Kerma can be constructed and members can "
            "be tested" ) {

        verifyChunkWithParticle( chunk );
      } // THEN

      THEN( "the record can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output );

        CHECK( buffer == record );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a Kerma instance" ) {

    WHEN( "the number of boundary values is insufficient" ) {

      THEN( "an exception is thrown" ) {

        std::vector< double > empty = {};

        CHECK_THROWS( Kerma( std::move( empty ) ) );
      } // THEN
    } // WHEN

    WHEN( "reading the data of the record and the number of boundary "
          "values is insufficient" ) {

      std::string record = chunkWithInsufficientNumberValues();
      auto iter = record.begin() + 8;
      auto end = record.end();
      Kerma chunk;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( chunk.read( iter, end, 0 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return "kerma\n"
         "    10 9 8 7 6\n"
         "    5 4\n";
}

void verifyChunk( const Kerma& chunk ) {

  CHECK( "kerma" == chunk.keyword() );
  CHECK( false == chunk.empty() );
  CHECK( 7 == chunk.size() );
  CHECK( 7 == chunk.values().size() );
  CHECK( 7 == chunk.numberGroups() );
  CHECK( std::nullopt == chunk.particle() );
  CHECK_THAT( 10, WithinRel( chunk.values()[0] ) );
  CHECK_THAT(  9, WithinRel( chunk.values()[1] ) );
  CHECK_THAT(  8, WithinRel( chunk.values()[2] ) );
  CHECK_THAT(  7, WithinRel( chunk.values()[3] ) );
  CHECK_THAT(  6, WithinRel( chunk.values()[4] ) );
  CHECK_THAT(  5, WithinRel( chunk.values()[5] ) );
  CHECK_THAT(  4, WithinRel( chunk.values()[6] ) );
}

std::string chunkWithParticle() {

  return "kerma_1001\n"
         "    10 9 8 7 6\n"
         "    5 4\n";
}

void verifyChunkWithParticle( const Kerma& chunk ) {

  CHECK( "kerma_1001" == chunk.keyword() );
  CHECK( false == chunk.empty() );
  CHECK( 7 == chunk.size() );
  CHECK( 7 == chunk.values().size() );
  CHECK( 7 == chunk.numberGroups() );
  CHECK( 1001 == chunk.particle() );
  CHECK_THAT( 10, WithinRel( chunk.values()[0] ) );
  CHECK_THAT(  9, WithinRel( chunk.values()[1] ) );
  CHECK_THAT(  8, WithinRel( chunk.values()[2] ) );
  CHECK_THAT(  7, WithinRel( chunk.values()[3] ) );
  CHECK_THAT(  6, WithinRel( chunk.values()[4] ) );
  CHECK_THAT(  5, WithinRel( chunk.values()[5] ) );
  CHECK_THAT(  4, WithinRel( chunk.values()[6] ) );
}

std::string chunkWithInsufficientNumberValues() {

  return "kerma_1001\n";
}
