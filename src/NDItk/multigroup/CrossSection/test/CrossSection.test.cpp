// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/multigroup/CrossSection.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using CrossSection = multigroup::CrossSection;

std::string chunk();
std::vector< double > data();
void verifyChunk( const CrossSection& );
std::vector< double > dataWithInsufficientLength();
std::vector< double > dataWithNonIntegerIdentifier();

SCENARIO( "CrossSection" ) {

  GIVEN( "valid data for a CrossSection instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      int reaction = 2;
      double qvalue = 0.0;
      std::vector< double > values = { 10., 20., 30., 40., 50., 60., 70. };

      CrossSection chunk( reaction, qvalue, std::move( values ) );

      THEN( "a CrossSection can be constructed and members can "
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

      CrossSection chunk( begin, end );

      THEN( "a CrossSection can be constructed and members can "
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

  GIVEN( "invalid data for a CrossSection instance" ) {

    WHEN( "the number of cross section values is insufficient" ) {

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CrossSection( 2, 0, {} ) );
      } // THEN
    } // WHEN

    WHEN( "using iterators and the number of cross section values is "
          "insufficient" ) {

      std::vector< double > values = dataWithInsufficientLength();
      auto begin = values.begin();
      auto end = values.end();

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CrossSection( begin, end ) );
      } // THEN
    } // WHEN

    WHEN( "using iterators and the reaction identifier is not an integer" ) {

      std::vector< double > values = dataWithNonIntegerIdentifier();
      auto begin = values.begin();
      auto end = values.end();

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CrossSection( begin, end ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return "    2 0\n"
         "    10 20 30 40 50\n"
         "    60 70\n";
}

std::vector< double > data() {

  return { 2, 0,
           10, 20, 30, 40, 50, 60, 70 };
}

void verifyChunk( const CrossSection& chunk ) {

  CHECK_THAT(  2, WithinRel( chunk.values()[0] ) );
  CHECK_THAT(  0, WithinRel( chunk.values()[1] ) );
  CHECK_THAT( 10, WithinRel( chunk.values()[2] ) );
  CHECK_THAT( 20, WithinRel( chunk.values()[3] ) );
  CHECK_THAT( 30, WithinRel( chunk.values()[4] ) );
  CHECK_THAT( 40, WithinRel( chunk.values()[5] ) );
  CHECK_THAT( 50, WithinRel( chunk.values()[6] ) );
  CHECK_THAT( 60, WithinRel( chunk.values()[7] ) );
  CHECK_THAT( 70, WithinRel( chunk.values()[8] ) );

  CHECK( false == chunk.empty() );
  CHECK( 9 == chunk.size() );

  CHECK( 7 == chunk.numberGroups() );
  CHECK( 2 == chunk.identifier() );
  CHECK_THAT( 0, WithinRel( chunk.qvalue() ) );
  CHECK_THAT( 10, WithinRel( chunk.crossSections()[0] ) );
  CHECK_THAT( 20, WithinRel( chunk.crossSections()[1] ) );
  CHECK_THAT( 30, WithinRel( chunk.crossSections()[2] ) );
  CHECK_THAT( 40, WithinRel( chunk.crossSections()[3] ) );
  CHECK_THAT( 50, WithinRel( chunk.crossSections()[4] ) );
  CHECK_THAT( 60, WithinRel( chunk.crossSections()[5] ) );
  CHECK_THAT( 70, WithinRel( chunk.crossSections()[6] ) );
}

std::vector< double > dataWithInsufficientLength() {

  return { 2, 0 };
}

std::vector< double > dataWithNonIntegerIdentifier() {

  return { 2.001, 0,
           10, 20, 30, 40, 50, 60, 70 };
}
