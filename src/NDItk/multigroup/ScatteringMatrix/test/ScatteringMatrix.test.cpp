// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/multigroup/ScatteringMatrix.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using ScatteringMatrix = multigroup::ScatteringMatrix;
using LegendreMoment = multigroup::LegendreMoment;

std::string chunk();
void verifyChunk( const ScatteringMatrix& );

SCENARIO( "ScatteringMatrix" ) {

  GIVEN( "valid data for a ScatteringMatrix instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< LegendreMoment > moments = {

        { 0, { 1, 2, 3, 4, 5, 6 }, 3, 2 },
        { 1, { 11, 12, 13, 14, 15, 16 }, 3, 2 }
      };

      ScatteringMatrix chunk( std::move( moments ) );

      THEN( "a ScatteringMatrix can be constructed and members can "
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

    WHEN( "the data is defined using iterators" ) {

      auto iter = record.begin() + 7;
      auto end = record.end();

      ScatteringMatrix chunk;
      chunk.read( iter, end, 3, 2, 2 );

      THEN( "a ScatteringMatrix can be constructed and members can "
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

  GIVEN( "invalid data for a ScatteringMatrix instance" ) {

    WHEN( "the number of moments is insufficient" ) {

      std::vector< LegendreMoment > moments = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ScatteringMatrix( std::move( moments ) ) );
      } // THEN
    } // WHEN

    WHEN( "the number of groups is inconsistent" ) {

      std::vector< LegendreMoment > moments = {

        { 0, { 1, 2, 3, 4, 5, 6 }, 3, 2 },       // <-- incident = 3, outgoing = 2
        { 1, { 11, 12, 13, 14, 15, 16 }, 2, 3 }  // <-- incident = 2, outgoing = 3
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ScatteringMatrix( std::move( moments ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return "pn_full\n"
         "    0\n"
         "    1 2 3 4 5\n"
         "    6\n"
         "    1\n"
         "    11 12 13 14 15\n"
         "    16\n";
}

void verifyChunk( const ScatteringMatrix& chunk ) {

  CHECK( "pn_full" == chunk.keyword() );
  CHECK_THAT( 0, WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 1, WithinRel( chunk.values()[1] ) );
  CHECK_THAT( 2, WithinRel( chunk.values()[2] ) );
  CHECK_THAT( 3, WithinRel( chunk.values()[3] ) );
  CHECK_THAT( 4, WithinRel( chunk.values()[4] ) );
  CHECK_THAT( 5, WithinRel( chunk.values()[5] ) );
  CHECK_THAT( 6, WithinRel( chunk.values()[6] ) );
  CHECK_THAT( 1, WithinRel( chunk.values()[7] ) );
  CHECK_THAT( 11, WithinRel( chunk.values()[8] ) );
  CHECK_THAT( 12, WithinRel( chunk.values()[9] ) );
  CHECK_THAT( 13, WithinRel( chunk.values()[10] ) );
  CHECK_THAT( 14, WithinRel( chunk.values()[11] ) );
  CHECK_THAT( 15, WithinRel( chunk.values()[12] ) );
  CHECK_THAT( 16, WithinRel( chunk.values()[13] ) );

  CHECK( false == chunk.empty() );
  CHECK( 14 == chunk.size() );

  CHECK( 3 == chunk.numberPrimaryGroups() );
  CHECK( 2 == chunk.numberOutgoingGroups() );
  CHECK( 2 == chunk.numberLegendreMoments() );

  CHECK( true == chunk.hasMoment( 0 ) );
  CHECK( true == chunk.hasMoment( 1 ) );
  CHECK( false == chunk.hasMoment( 102 ) );

  CHECK( 0 == chunk.moments()[0].order() );
  CHECK_THAT( 1, WithinRel( chunk.moments()[0].matrix()[0][0] ) );
  CHECK_THAT( 2, WithinRel( chunk.moments()[0].matrix()[0][1] ) );
  CHECK_THAT( 3, WithinRel( chunk.moments()[0].matrix()[1][0] ) );
  CHECK_THAT( 4, WithinRel( chunk.moments()[0].matrix()[1][1] ) );
  CHECK_THAT( 5, WithinRel( chunk.moments()[0].matrix()[2][0] ) );
  CHECK_THAT( 6, WithinRel( chunk.moments()[0].matrix()[2][1] ) );

  CHECK( 1 == chunk.moments()[1].order() );
  CHECK_THAT( 11, WithinRel( chunk.moments()[1].matrix()[0][0] ) );
  CHECK_THAT( 12, WithinRel( chunk.moments()[1].matrix()[0][1] ) );
  CHECK_THAT( 13, WithinRel( chunk.moments()[1].matrix()[1][0] ) );
  CHECK_THAT( 14, WithinRel( chunk.moments()[1].matrix()[1][1] ) );
  CHECK_THAT( 15, WithinRel( chunk.moments()[1].matrix()[2][0] ) );
  CHECK_THAT( 16, WithinRel( chunk.moments()[1].matrix()[2][1] ) );

  auto moment = chunk.moment( 0 );
  CHECK( 0 == moment.order() );
  CHECK_THAT( 1, WithinRel( moment.matrix()[0][0] ) );
  CHECK_THAT( 2, WithinRel( moment.matrix()[0][1] ) );
  CHECK_THAT( 3, WithinRel( moment.matrix()[1][0] ) );
  CHECK_THAT( 4, WithinRel( moment.matrix()[1][1] ) );
  CHECK_THAT( 5, WithinRel( moment.matrix()[2][0] ) );
  CHECK_THAT( 6, WithinRel( moment.matrix()[2][1] ) );

  moment = chunk.moment( 1 );
  CHECK( 1 == chunk.moments()[1].order() );
  CHECK_THAT( 11, WithinRel( moment.matrix()[0][0] ) );
  CHECK_THAT( 12, WithinRel( moment.matrix()[0][1] ) );
  CHECK_THAT( 13, WithinRel( moment.matrix()[1][0] ) );
  CHECK_THAT( 14, WithinRel( moment.matrix()[1][1] ) );
  CHECK_THAT( 15, WithinRel( moment.matrix()[2][0] ) );
  CHECK_THAT( 16, WithinRel( moment.matrix()[2][1] ) );
}
