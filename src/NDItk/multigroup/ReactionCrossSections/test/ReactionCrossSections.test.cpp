// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/multigroup/ReactionCrossSections.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using CrossSection = multigroup::CrossSection;
using ReactionCrossSections = multigroup::ReactionCrossSections;

std::string chunk();
std::vector< double > data();
void verifyChunk( const ReactionCrossSections& );

SCENARIO( "ReactionCrossSections" ) {

  GIVEN( "valid data for a ReactionCrossSections instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< CrossSection > xs = {

        { 2, 0.0, { 10., 20., 30., 40., 50., 60., 70. } },
        { 16, 1.1234567, { 1., 2., 3., 4., 5., 6., 7. } }
      };

      ReactionCrossSections chunk( std::move( xs ) );

      THEN( "a ReactionCrossSections can be constructed and members can "
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

      auto iter = record.begin() + 8;
      auto end = record.end();

      ReactionCrossSections chunk;
      chunk.read( iter, end, 2, 7 );

      THEN( "a ReactionCrossSections can be constructed and members can "
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

  return "sig_reac\n"
         "                   2                   0\n"
         "                  10                  20                  30                  40\n"
         "                  50                  60                  70\n"
         "                  16           1.1234567\n"
         "                   1                   2                   3                   4\n"
         "                   5                   6                   7\n";
}

void verifyChunk( const ReactionCrossSections& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 2 == chunk.numberReactions() );
  CHECK( 7 == chunk.numberGroups() );

  CHECK( true == chunk.hasReaction( 2 ) );
  CHECK( true == chunk.hasReaction( 16 ) );
  CHECK( false == chunk.hasReaction( 102 ) );

  CHECK( 2 == chunk.reactions()[0].reaction() );
  CHECK_THAT( 0.0, WithinRel( chunk.reactions()[0].qvalue() ) );
  CHECK_THAT( 10.0, WithinRel( chunk.reactions()[0].crossSections()[0] ) );
  CHECK_THAT( 20.0, WithinRel( chunk.reactions()[0].crossSections()[1] ) );
  CHECK_THAT( 30.0, WithinRel( chunk.reactions()[0].crossSections()[2] ) );
  CHECK_THAT( 40.0, WithinRel( chunk.reactions()[0].crossSections()[3] ) );
  CHECK_THAT( 50.0, WithinRel( chunk.reactions()[0].crossSections()[4] ) );
  CHECK_THAT( 60.0, WithinRel( chunk.reactions()[0].crossSections()[5] ) );
  CHECK_THAT( 70.0, WithinRel( chunk.reactions()[0].crossSections()[6] ) );

  CHECK( 16 == chunk.reactions()[1].reaction() );
  CHECK_THAT( 1.1234567, WithinRel( chunk.reactions()[1].qvalue() ) );
  CHECK_THAT( 1.0, WithinRel( chunk.reactions()[1].crossSections()[0] ) );
  CHECK_THAT( 2.0, WithinRel( chunk.reactions()[1].crossSections()[1] ) );
  CHECK_THAT( 3.0, WithinRel( chunk.reactions()[1].crossSections()[2] ) );
  CHECK_THAT( 4.0, WithinRel( chunk.reactions()[1].crossSections()[3] ) );
  CHECK_THAT( 5.0, WithinRel( chunk.reactions()[1].crossSections()[4] ) );
  CHECK_THAT( 6.0, WithinRel( chunk.reactions()[1].crossSections()[5] ) );
  CHECK_THAT( 7.0, WithinRel( chunk.reactions()[1].crossSections()[6] ) );

  auto xs = chunk.crossSection( 2 );
  CHECK( 2 == xs.reaction() );
  CHECK_THAT( 0.0, WithinRel( xs.qvalue() ) );
  CHECK_THAT( 10.0, WithinRel( xs.crossSections()[0] ) );
  CHECK_THAT( 20.0, WithinRel( xs.crossSections()[1] ) );
  CHECK_THAT( 30.0, WithinRel( xs.crossSections()[2] ) );
  CHECK_THAT( 40.0, WithinRel( xs.crossSections()[3] ) );
  CHECK_THAT( 50.0, WithinRel( xs.crossSections()[4] ) );
  CHECK_THAT( 60.0, WithinRel( xs.crossSections()[5] ) );
  CHECK_THAT( 70.0, WithinRel( xs.crossSections()[6] ) );

  xs = chunk.crossSection( 16 );
  CHECK( 16 == xs.reaction() );
  CHECK_THAT( 1.1234567, WithinRel( xs.qvalue() ) );
  CHECK_THAT( 1.0, WithinRel( xs.crossSections()[0] ) );
  CHECK_THAT( 2.0, WithinRel( xs.crossSections()[1] ) );
  CHECK_THAT( 3.0, WithinRel( xs.crossSections()[2] ) );
  CHECK_THAT( 4.0, WithinRel( xs.crossSections()[3] ) );
  CHECK_THAT( 5.0, WithinRel( xs.crossSections()[4] ) );
  CHECK_THAT( 6.0, WithinRel( xs.crossSections()[5] ) );
  CHECK_THAT( 7.0, WithinRel( xs.crossSections()[6] ) );
}
