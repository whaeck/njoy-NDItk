// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/multigroup/AverageFissionEnergyRelease.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using AverageFissionEnergyRelease = multigroup::AverageFissionEnergyRelease;

std::string chunk();
void verifyChunk( const AverageFissionEnergyRelease& );

SCENARIO( "AverageFissionEnergyRelease" ) {

  GIVEN( "valid data for a AverageFissionEnergyRelease instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      double total = 202.827;
      double prompt = 181.238898;
      double neutrons = 4.827645;
      double gammas = 7.281253;
      double betas = 6.5;
      double fragments = 169.13;
      AverageFissionEnergyRelease chunk( total, prompt, neutrons,
                                         gammas, betas, fragments );

      THEN( "a AverageFissionEnergyRelease can be constructed and members can "
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

      auto iter = record.begin() + 6;
      auto end = record.end();

      AverageFissionEnergyRelease chunk;
      chunk.read( iter, end );

      THEN( "a AverageFissionEnergyRelease can be constructed and members can "
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

  return "fiss_q\n"
         "    181.238898 202.827 6.5 7.281253 169.13\n"
         "    4.827645\n";
}

void verifyChunk( const AverageFissionEnergyRelease& chunk ) {

  CHECK( "fiss_q" == chunk.keyword() );
  CHECK_THAT( 181.238898, WithinRel( chunk.values()[0] ) );
  CHECK_THAT(    202.827, WithinRel( chunk.values()[1] ) );
  CHECK_THAT(        6.5, WithinRel( chunk.values()[2] ) );
  CHECK_THAT(   7.281253, WithinRel( chunk.values()[3] ) );
  CHECK_THAT(     169.13, WithinRel( chunk.values()[4] ) );
  CHECK_THAT(   4.827645, WithinRel( chunk.values()[5] ) );

  CHECK( false == chunk.empty() );
  CHECK( 6 == chunk.size() );

  CHECK_THAT( 181.238898, WithinRel( chunk.promptEnergyRelease() ) );
  CHECK_THAT(    202.827, WithinRel( chunk.totalEnergyRelease() ) );
  CHECK_THAT(        6.5, WithinRel( chunk.delayedBetas() ) );
  CHECK_THAT(   7.281253, WithinRel( chunk.promptGammas() ) );
  CHECK_THAT(     169.13, WithinRel( chunk.fissionFragments() ) );
  CHECK_THAT(   4.827645, WithinRel( chunk.promptNeutrons() ) );
}
