// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/multigroup/LegendreMoment.hpp"
#include "tools/std23/views.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using LegendreMoment = multigroup::LegendreMoment;

std::string chunk();
std::vector< double > data();
void verifyChunk( const LegendreMoment& );
std::vector< double > dataWithInsufficientLength();

SCENARIO( "LegendreMoment" ) {

  GIVEN( "valid data for a LegendreMoment instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      int order = 2;
      std::vector< double > values = {  1.,  2.,  3.,
                                        4.,  5.,  6.,
                                        7.,  8.,  9.,
                                       10., 11., 12. };
      std::size_t incident = 4;
      std::size_t outgoing = 3;

      LegendreMoment chunk( order, std::move( values ), incident, outgoing );

      THEN( "a LegendreMoment can be constructed and members can "
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

      std::vector< double > values = data();
      auto begin = values.begin();
      auto end = values.end();

      LegendreMoment chunk( begin, end, 4, 3 );

      THEN( "a LegendreMoment can be constructed and members can "
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

  GIVEN( "invalid data for a LegendreMoment instance" ) {

    WHEN( "the number of cross section values is insufficient" ) {

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LegendreMoment( 2, {}, 4, 3 ) );
      } // THEN
    } // WHEN

    WHEN( "using iterators and the number of cross section values is "
          "insufficient" ) {

      std::vector< double > values = dataWithInsufficientLength();
      auto begin = values.begin();
      auto end = values.end();

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LegendreMoment( begin, end, 4, 3 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return "    2\n"
         "    1 2 3 4 5\n"
         "    6 7 8 9 10\n"
         "    11 12\n";
}

std::vector< double > data() {

  return {  2,
            1.,  2.,  3.,
            4.,  5.,  6.,
            7.,  8.,  9.,
           10., 11., 12. };
}

void verifyChunk( const LegendreMoment& chunk ) {

  CHECK( 2 == chunk.order() );
  CHECK( 4 == chunk.numberPrimaryGroups() );
  CHECK( 3 == chunk.numberOutgoingGroups() );
  CHECK_THAT(  1, WithinRel( chunk.matrix()[0][0] ) );
  CHECK_THAT(  2, WithinRel( chunk.matrix()[0][1] ) );
  CHECK_THAT(  3, WithinRel( chunk.matrix()[0][2] ) );
  CHECK_THAT(  4, WithinRel( chunk.matrix()[1][0] ) );
  CHECK_THAT(  5, WithinRel( chunk.matrix()[1][1] ) );
  CHECK_THAT(  6, WithinRel( chunk.matrix()[1][2] ) );
  CHECK_THAT(  7, WithinRel( chunk.matrix()[2][0] ) );
  CHECK_THAT(  8, WithinRel( chunk.matrix()[2][1] ) );
  CHECK_THAT(  9, WithinRel( chunk.matrix()[2][2] ) );
  CHECK_THAT( 10, WithinRel( chunk.matrix()[3][0] ) );
  CHECK_THAT( 11, WithinRel( chunk.matrix()[3][1] ) );
  CHECK_THAT( 12, WithinRel( chunk.matrix()[3][2] ) );

  CHECK_THAT(  2, WithinRel( chunk.values()[0] ) );
  CHECK_THAT(  1, WithinRel( chunk.values()[1] ) );
  CHECK_THAT(  2, WithinRel( chunk.values()[2] ) );
  CHECK_THAT(  3, WithinRel( chunk.values()[3] ) );
  CHECK_THAT(  4, WithinRel( chunk.values()[4] ) );
  CHECK_THAT(  5, WithinRel( chunk.values()[5] ) );
  CHECK_THAT(  6, WithinRel( chunk.values()[6] ) );
  CHECK_THAT(  7, WithinRel( chunk.values()[7] ) );
  CHECK_THAT(  8, WithinRel( chunk.values()[8] ) );
  CHECK_THAT(  9, WithinRel( chunk.values()[9] ) );
  CHECK_THAT( 10, WithinRel( chunk.values()[10] ) );
  CHECK_THAT( 11, WithinRel( chunk.values()[11] ) );
  CHECK_THAT( 12, WithinRel( chunk.values()[12] ) );

  CHECK( false == chunk.empty() );
  CHECK( 13 == chunk.size() );
}

std::vector< double > dataWithInsufficientLength() {

  return { 2 };
}
