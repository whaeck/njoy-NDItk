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
std::string chunkForProductionMatrix();
void verifyChunkForProductionMatrix( const ScatteringMatrix& );
ScatteringMatrix makeDummyRecord();

SCENARIO( "ScatteringMatrix" ) {

  GIVEN( "valid data for a ScatteringMatrix instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< LegendreMoment > moments = {

        { 0, { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, 3 },
        { 1, { 11, 12, 13, 14, 15, 16, 17, 18, 19 }, 3 }
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
      chunk.read( iter, end, 3, 2 );

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

    WHEN( "using the copy constructor" ) {

      auto iter = record.begin() + 7;
      auto end = record.end();
      ScatteringMatrix chunk;
      chunk.read( iter, end, 3, 2 );

      ScatteringMatrix copy( chunk );

      THEN( "a ScatteringMatrix can be constructed and members can "
            "be tested" ) {

        verifyChunk( copy );
      } // THEN

      THEN( "the record can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        copy.print( output );

        CHECK( buffer == record );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      auto iter = record.begin() + 7;
      auto end = record.end();
      ScatteringMatrix chunk;
      chunk.read( iter, end, 3, 2 );

      ScatteringMatrix move( std::move( chunk ) );

      THEN( "a ScatteringMatrix can be constructed and members can "
            "be tested" ) {

        verifyChunk( move );
      } // THEN

      THEN( "the record can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        move.print( output );

        CHECK( buffer == record );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      auto iter = record.begin() + 7;
      auto end = record.end();
      ScatteringMatrix chunk;
      chunk.read( iter, end, 3, 2 );

      ScatteringMatrix copy = makeDummyRecord();
      copy = chunk;

      THEN( "a ScatteringMatrix can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( copy );
      } // THEN

      THEN( "the record can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        copy.print( output );

        CHECK( buffer == record );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      auto iter = record.begin() + 7;
      auto end = record.end();
      ScatteringMatrix chunk;
      chunk.read( iter, end, 3, 2 );

      ScatteringMatrix move = makeDummyRecord();
      move = std::move( chunk );

      THEN( "a ScatteringMatrix can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( move );
      } // THEN

      THEN( "the record can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        move.print( output );

        CHECK( buffer == record );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a ScatteringMatrix instance for a secondary particle" ) {

    std::string record = chunkForProductionMatrix();

    WHEN( "the data is given explicitly" ) {

      std::vector< LegendreMoment > moments = {

        { 0, { 1, 2, 3, 4, 5, 6 }, 3, 2 },
        { 1, { 11, 12, 13, 14, 15, 16 }, 3, 2 }
      };

      ScatteringMatrix chunk( 1001, std::move( moments ) );

      THEN( "a ScatteringMatrix can be constructed and members can "
            "be tested" ) {

        verifyChunkForProductionMatrix( chunk );
      } // THEN

      THEN( "the record can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output );

        CHECK( buffer == record );
      } // THEN
    } // WHEN

    WHEN( "the data is defined using iterators" ) {

      auto iter = record.begin() + 17;
      auto end = record.end();

      ScatteringMatrix chunk( 1001 );
      chunk.read( iter, end, 3, 2, 2 );

      THEN( "a ScatteringMatrix can be constructed and members can "
            "be tested" ) {

        verifyChunkForProductionMatrix( chunk );
      } // THEN

      THEN( "the record can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output );

        CHECK( buffer == record );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      auto iter = record.begin() + 17;
      auto end = record.end();
      ScatteringMatrix chunk( 1001 );
      chunk.read( iter, end, 3, 2, 2 );

      ScatteringMatrix copy( chunk );

      THEN( "a ScatteringMatrix can be constructed and members can "
            "be tested" ) {

        verifyChunkForProductionMatrix( copy );
      } // THEN

      THEN( "the record can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        copy.print( output );

        CHECK( buffer == record );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      auto iter = record.begin() + 17;
      auto end = record.end();
      ScatteringMatrix chunk( 1001 );
      chunk.read( iter, end, 3, 2, 2 );

      ScatteringMatrix move( std::move( chunk ) );

      THEN( "a ScatteringMatrix can be constructed and members can "
            "be tested" ) {

        verifyChunkForProductionMatrix( move );
      } // THEN

      THEN( "the record can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        move.print( output );

        CHECK( buffer == record );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      auto iter = record.begin() + 17;
      auto end = record.end();
      ScatteringMatrix chunk( 1001 );
      chunk.read( iter, end, 3, 2, 2 );

      ScatteringMatrix copy = makeDummyRecord();
      copy = chunk;

      THEN( "a ScatteringMatrix can be copy assigned and "
            "members can be tested" ) {

        verifyChunkForProductionMatrix( copy );
      } // THEN

      THEN( "the record can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        copy.print( output );

        CHECK( buffer == record );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      auto iter = record.begin() + 17;
      auto end = record.end();
      ScatteringMatrix chunk( 1001 );
      chunk.read( iter, end, 3, 2, 2 );

      ScatteringMatrix move = makeDummyRecord();
      move = std::move( chunk );

      THEN( "a ScatteringMatrix can be copy assigned and "
            "members can be tested" ) {

        verifyChunkForProductionMatrix( move );
      } // THEN

      THEN( "the record can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        move.print( output );

        CHECK( buffer == record );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a ScatteringMatrix instance" ) {

    WHEN( "the number of moments is insufficient" ) {

      std::vector< LegendreMoment > moments = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ScatteringMatrix( std::move( moments ) ) );
        CHECK_THROWS( ScatteringMatrix( 1001, std::move( moments ) ) );
      } // THEN
    } // WHEN

    WHEN( "the number of groups is inconsistent" ) {

      std::vector< LegendreMoment > moments1 = {

        { 0, { 1, 2, 3, 4 }, 2 },                         // <-- incident = 3
        { 1, { 11, 12, 13, 14, 15, 16, 17, 18, 19 }, 3 }  // <-- incident = 2
      };

      std::vector< LegendreMoment > moments2 = {

        { 0, { 1, 2, 3, 4, 5, 6 }, 3, 2 },       // <-- incident = 3, outgoing = 2
        { 1, { 11, 12, 13, 14, 15, 16 }, 2, 3 }  // <-- incident = 2, outgoing = 3
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ScatteringMatrix( std::move( moments1 ) ) );
        CHECK_THROWS( ScatteringMatrix( 1001, std::move( moments2 ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return "pn_full\n"
         "    0\n"
         "    1 2 3 4 5\n"
         "    6 7 8 9\n"
         "    1\n"
         "    11 12 13 14 15\n"
         "    16 17 18 19\n";
}

void verifyChunk( const ScatteringMatrix& chunk ) {

  CHECK( "pn_full" == chunk.keyword() );
  CHECK( std::nullopt == chunk.particle() );
  CHECK_THAT( 0, WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 1, WithinRel( chunk.values()[1] ) );
  CHECK_THAT( 2, WithinRel( chunk.values()[2] ) );
  CHECK_THAT( 3, WithinRel( chunk.values()[3] ) );
  CHECK_THAT( 4, WithinRel( chunk.values()[4] ) );
  CHECK_THAT( 5, WithinRel( chunk.values()[5] ) );
  CHECK_THAT( 6, WithinRel( chunk.values()[6] ) );
  CHECK_THAT( 7, WithinRel( chunk.values()[7] ) );
  CHECK_THAT( 8, WithinRel( chunk.values()[8] ) );
  CHECK_THAT( 9, WithinRel( chunk.values()[9] ) );
  CHECK_THAT( 1, WithinRel( chunk.values()[10] ) );
  CHECK_THAT( 11, WithinRel( chunk.values()[11] ) );
  CHECK_THAT( 12, WithinRel( chunk.values()[12] ) );
  CHECK_THAT( 13, WithinRel( chunk.values()[13] ) );
  CHECK_THAT( 14, WithinRel( chunk.values()[14] ) );
  CHECK_THAT( 15, WithinRel( chunk.values()[15] ) );
  CHECK_THAT( 16, WithinRel( chunk.values()[16] ) );
  CHECK_THAT( 17, WithinRel( chunk.values()[17] ) );
  CHECK_THAT( 18, WithinRel( chunk.values()[18] ) );
  CHECK_THAT( 19, WithinRel( chunk.values()[19] ) );

  CHECK( false == chunk.empty() );
  CHECK( 20 == chunk.size() );

  CHECK( 3 == chunk.numberPrimaryGroups() );
  CHECK( 3 == chunk.numberOutgoingGroups() );
  CHECK( 2 == chunk.numberLegendreMoments() );

  CHECK( true == chunk.hasMoment( 0 ) );
  CHECK( true == chunk.hasMoment( 1 ) );
  CHECK( false == chunk.hasMoment( 102 ) );

  CHECK( 0 == chunk.moments()[0].order() );
  CHECK_THAT( 1, WithinRel( chunk.moments()[0].matrix()[0][0] ) );
  CHECK_THAT( 2, WithinRel( chunk.moments()[0].matrix()[0][1] ) );
  CHECK_THAT( 3, WithinRel( chunk.moments()[0].matrix()[0][2] ) );
  CHECK_THAT( 4, WithinRel( chunk.moments()[0].matrix()[1][0] ) );
  CHECK_THAT( 5, WithinRel( chunk.moments()[0].matrix()[1][1] ) );
  CHECK_THAT( 6, WithinRel( chunk.moments()[0].matrix()[1][2] ) );
  CHECK_THAT( 7, WithinRel( chunk.moments()[0].matrix()[2][0] ) );
  CHECK_THAT( 8, WithinRel( chunk.moments()[0].matrix()[2][1] ) );
  CHECK_THAT( 9, WithinRel( chunk.moments()[0].matrix()[2][2] ) );

  CHECK( 1 == chunk.moments()[1].order() );
  CHECK_THAT( 11, WithinRel( chunk.moments()[1].matrix()[0][0] ) );
  CHECK_THAT( 12, WithinRel( chunk.moments()[1].matrix()[0][1] ) );
  CHECK_THAT( 13, WithinRel( chunk.moments()[1].matrix()[0][2] ) );
  CHECK_THAT( 14, WithinRel( chunk.moments()[1].matrix()[1][0] ) );
  CHECK_THAT( 15, WithinRel( chunk.moments()[1].matrix()[1][1] ) );
  CHECK_THAT( 16, WithinRel( chunk.moments()[1].matrix()[1][2] ) );
  CHECK_THAT( 17, WithinRel( chunk.moments()[1].matrix()[2][0] ) );
  CHECK_THAT( 18, WithinRel( chunk.moments()[1].matrix()[2][1] ) );
  CHECK_THAT( 19, WithinRel( chunk.moments()[1].matrix()[2][2] ) );

  auto moment = chunk.moment( 0 );
  CHECK( 0 == moment.order() );
  CHECK_THAT( 1, WithinRel( moment.matrix()[0][0] ) );
  CHECK_THAT( 2, WithinRel( moment.matrix()[0][1] ) );
  CHECK_THAT( 3, WithinRel( moment.matrix()[0][2] ) );
  CHECK_THAT( 4, WithinRel( moment.matrix()[1][0] ) );
  CHECK_THAT( 5, WithinRel( moment.matrix()[1][1] ) );
  CHECK_THAT( 6, WithinRel( moment.matrix()[1][2] ) );
  CHECK_THAT( 7, WithinRel( moment.matrix()[2][0] ) );
  CHECK_THAT( 8, WithinRel( moment.matrix()[2][1] ) );
  CHECK_THAT( 9, WithinRel( moment.matrix()[2][2] ) );

  moment = chunk.moment( 1 );
  CHECK( 1 == moment.order() );
  CHECK_THAT( 11, WithinRel( moment.matrix()[0][0] ) );
  CHECK_THAT( 12, WithinRel( moment.matrix()[0][1] ) );
  CHECK_THAT( 13, WithinRel( moment.matrix()[0][2] ) );
  CHECK_THAT( 14, WithinRel( moment.matrix()[1][0] ) );
  CHECK_THAT( 15, WithinRel( moment.matrix()[1][1] ) );
  CHECK_THAT( 16, WithinRel( moment.matrix()[1][2] ) );
  CHECK_THAT( 17, WithinRel( moment.matrix()[2][0] ) );
  CHECK_THAT( 18, WithinRel( moment.matrix()[2][1] ) );
  CHECK_THAT( 19, WithinRel( moment.matrix()[2][2] ) );
}

std::string chunkForProductionMatrix() {

  return "pn_prod_full_1001\n"
         "    0\n"
         "    1 2 3 4 5\n"
         "    6\n"
         "    1\n"
         "    11 12 13 14 15\n"
         "    16\n";
}

void verifyChunkForProductionMatrix( const ScatteringMatrix& chunk ) {

  CHECK( "pn_prod_full_1001" == chunk.keyword() );
  CHECK( 1001 == chunk.particle() );
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
  CHECK( 1 == moment.order() );
  CHECK_THAT( 11, WithinRel( moment.matrix()[0][0] ) );
  CHECK_THAT( 12, WithinRel( moment.matrix()[0][1] ) );
  CHECK_THAT( 13, WithinRel( moment.matrix()[1][0] ) );
  CHECK_THAT( 14, WithinRel( moment.matrix()[1][1] ) );
  CHECK_THAT( 15, WithinRel( moment.matrix()[2][0] ) );
  CHECK_THAT( 16, WithinRel( moment.matrix()[2][1] ) );
}

ScatteringMatrix makeDummyRecord() {

  return { { { 0, { 1, 2, 3, 4 }, 2 } } };
}
