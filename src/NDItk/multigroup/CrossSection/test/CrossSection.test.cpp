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
} // SCENARIO

std::string chunk() {

  return "                   2                   0\n"
         "                  10                  20                  30                  40\n"
         "                  50                  60                  70\n";
}

std::vector< double > data() {

  return { 2, 0,
           10, 20, 30, 40, 50, 60, 70 };
}

void verifyChunk( const CrossSection& chunk ) {

  CHECK( true == chunk.hasContent() );
  CHECK( 2 == chunk.reaction() );
  CHECK( 7 == chunk.numberGroups() );
  CHECK_THAT( 10, WithinRel( chunk.crossSections()[0] ) );
  CHECK_THAT( 20, WithinRel( chunk.crossSections()[1] ) );
  CHECK_THAT( 30, WithinRel( chunk.crossSections()[2] ) );
  CHECK_THAT( 40, WithinRel( chunk.crossSections()[3] ) );
  CHECK_THAT( 50, WithinRel( chunk.crossSections()[4] ) );
  CHECK_THAT( 60, WithinRel( chunk.crossSections()[5] ) );
  CHECK_THAT( 70, WithinRel( chunk.crossSections()[6] ) );
}
