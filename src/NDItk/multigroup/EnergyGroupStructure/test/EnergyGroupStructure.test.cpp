// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/multigroup/EnergyGroupStructure.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using EnergyGroupStructure = multigroup::EnergyGroupStructure;

std::string chunk();
void verifyChunk( const EnergyGroupStructure& );
std::string chunkWithParticle();
void verifyChunkWithParticle( const EnergyGroupStructure& );
std::string chunkWithInsufficientNumberBoundaries();
std::string chunkWithNonDescendingBoundaries();
std::string chunkWithNonUniqueBoundaries();

SCENARIO( "EnergyGroupStructure" ) {

  GIVEN( "valid data for a primary EnergyGroupStructure instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > boundaries = { 20., 18., 16., 14., 10., 5, 1, 1e-11 };

      EnergyGroupStructure chunk( std::move( boundaries ) );

      THEN( "a EnergyGroupStructure can be constructed and members can "
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

      EnergyGroupStructure chunk;
      chunk.read( iter, end, 8 );

      THEN( "a EnergyGroupStructure can be constructed and members can "
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

  GIVEN( "valid data for a outgoing EnergyGroupStructure instance" ) {

    std::string record = chunkWithParticle();

    WHEN( "the data is given explicitly" ) {

      unsigned int particle = 1001;
      std::vector< double > boundaries = { 20., 18., 16., 14., 10., 5, 1, 1e-11 };

      EnergyGroupStructure chunk( particle, std::move( boundaries ) );

      THEN( "a EnergyGroupStructure can be constructed and members can "
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

      auto iter = record.begin() + 13;
      auto end = record.end();

      EnergyGroupStructure chunk( 1001 );
      chunk.read( iter, end, 8 );

      THEN( "a EnergyGroupStructure can be constructed and members can "
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

  GIVEN( "invalid data for a EnergyGroupStructure instance" ) {

    WHEN( "the number of boundary values is insufficient" ) {

      THEN( "an exception is thrown" ) {

        std::vector< double > empty = {};
        std::vector< double > one = { 1 };

        CHECK_THROWS( EnergyGroupStructure( std::move( empty ) ) );
        CHECK_THROWS( EnergyGroupStructure( std::move( one ) ) );
      } // THEN
    } // WHEN

    WHEN( "the boundary values are not in descending order" ) {

      THEN( "an exception is thrown" ) {

        std::vector< double > wrong = { 1., 20. };

        CHECK_THROWS( EnergyGroupStructure( std::move( wrong ) ) );
      } // THEN
    } // WHEN

    WHEN( "the boundary values are not unique" ) {

      THEN( "an exception is thrown" ) {

        std::vector< double > wrong = { 20., 20., 5. };

        CHECK_THROWS( EnergyGroupStructure( std::move( wrong ) ) );
      } // THEN
    } // WHEN

    WHEN( "reading the data of the record and the number of boundary "
          "values is insufficient" ) {

      std::string record = chunkWithInsufficientNumberBoundaries();
      auto iter = record.begin() + 8;
      auto end = record.end();
      EnergyGroupStructure chunk;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( chunk.read( iter, end, 1 ) );
      } // THEN
    } // WHEN

    WHEN( "reading the data of the record and the boundary values"
          "are not in descending order" ) {

      std::string record = chunkWithNonDescendingBoundaries();
      auto iter = record.begin() + 8;
      auto end = record.end();
      EnergyGroupStructure chunk;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( chunk.read( iter, end, 2 ) );
      } // THEN
    } // WHEN

    WHEN( "the boundary values are not unique" ) {

      std::string record = chunkWithNonUniqueBoundaries();
      auto iter = record.begin() + 8;
      auto end = record.end();
      EnergyGroupStructure chunk;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( chunk.read( iter, end, 3 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return "e_bounds\n"
         "    20 18 16 14 10\n"
         "    5 1 1e-11\n";
}

void verifyChunk( const EnergyGroupStructure& chunk ) {

  CHECK( "e_bounds" == chunk.keyword() );
  CHECK( std::nullopt == chunk.particle() );
  CHECK_THAT(    20, WithinRel( chunk.values()[0] ) );
  CHECK_THAT(    18, WithinRel( chunk.values()[1] ) );
  CHECK_THAT(    16, WithinRel( chunk.values()[2] ) );
  CHECK_THAT(    14, WithinRel( chunk.values()[3] ) );
  CHECK_THAT(    10, WithinRel( chunk.values()[4] ) );
  CHECK_THAT(     5, WithinRel( chunk.values()[5] ) );
  CHECK_THAT(     1, WithinRel( chunk.values()[6] ) );
  CHECK_THAT( 1e-11, WithinRel( chunk.values()[7] ) );

  CHECK( false == chunk.empty() );
  CHECK( 8 == chunk.size() );

  CHECK( 8 == chunk.boundaries().size() );
  CHECK( 7 == chunk.numberGroups() );
  CHECK_THAT(    20, WithinRel( chunk.boundaries()[0] ) );
  CHECK_THAT(    18, WithinRel( chunk.boundaries()[1] ) );
  CHECK_THAT(    16, WithinRel( chunk.boundaries()[2] ) );
  CHECK_THAT(    14, WithinRel( chunk.boundaries()[3] ) );
  CHECK_THAT(    10, WithinRel( chunk.boundaries()[4] ) );
  CHECK_THAT(     5, WithinRel( chunk.boundaries()[5] ) );
  CHECK_THAT(     1, WithinRel( chunk.boundaries()[6] ) );
  CHECK_THAT( 1e-11, WithinRel( chunk.boundaries()[7] ) );
}

std::string chunkWithParticle() {

  return "e_bounds_1001\n"
         "    20 18 16 14 10\n"
         "    5 1 1e-11\n";
}

void verifyChunkWithParticle( const EnergyGroupStructure& chunk ) {

  CHECK( "e_bounds_1001" == chunk.keyword() );
  CHECK( 1001 == chunk.particle() );
  CHECK_THAT(    20, WithinRel( chunk.values()[0] ) );
  CHECK_THAT(    18, WithinRel( chunk.values()[1] ) );
  CHECK_THAT(    16, WithinRel( chunk.values()[2] ) );
  CHECK_THAT(    14, WithinRel( chunk.values()[3] ) );
  CHECK_THAT(    10, WithinRel( chunk.values()[4] ) );
  CHECK_THAT(     5, WithinRel( chunk.values()[5] ) );
  CHECK_THAT(     1, WithinRel( chunk.values()[6] ) );
  CHECK_THAT( 1e-11, WithinRel( chunk.values()[7] ) );

  CHECK( false == chunk.empty() );
  CHECK( 8 == chunk.size() );

  CHECK( 8 == chunk.boundaries().size() );
  CHECK( 7 == chunk.numberGroups() );
  CHECK_THAT(    20, WithinRel( chunk.boundaries()[0] ) );
  CHECK_THAT(    18, WithinRel( chunk.boundaries()[1] ) );
  CHECK_THAT(    16, WithinRel( chunk.boundaries()[2] ) );
  CHECK_THAT(    14, WithinRel( chunk.boundaries()[3] ) );
  CHECK_THAT(    10, WithinRel( chunk.boundaries()[4] ) );
  CHECK_THAT(     5, WithinRel( chunk.boundaries()[5] ) );
  CHECK_THAT(     1, WithinRel( chunk.boundaries()[6] ) );
  CHECK_THAT( 1e-11, WithinRel( chunk.boundaries()[7] ) );
}

std::string chunkWithInsufficientNumberBoundaries() {

  return "e_bounds\n"
         "    20\n";
}

std::string chunkWithNonDescendingBoundaries() {

  return "e_bounds\n"
         "    1 20\n";
}

std::string chunkWithNonUniqueBoundaries() {

  return "e_bounds\n"
         "    20 20 5\n";
}
