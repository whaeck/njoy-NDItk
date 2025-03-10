// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/depletion/IncidentParticle.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using IncidentParticle = depletion::IncidentParticle;
using Target           = depletion::Target;
using Product          = depletion::Product;

std::string chunk();
void verifyChunk( const IncidentParticle& );
std::string chunkWithInsufficientNumberTargets();
IncidentParticle makeDummyRecord();

SCENARIO( "IncidentParticle" ) {

  GIVEN( "valid data for a IncidentParticle instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< Target > targets = {
          Target(1001, { Product({1002, {102}, {1}}) }),
          Target(1002, { Product({1001, {16}, {1}}), Product({1003, {102}, {1}}) })
      };

      IncidentParticle chunk( 1, targets );

      THEN( "an IncidentParticle can be constructed and members can be tested" ) {

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

      IncidentParticle chunk;
      chunk.read( iter, end );

      THEN( "an IncidentParticle can be constructed and members can be tested" ) {

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

      auto iter = record.begin() + 8;
      auto end = record.end();
      IncidentParticle chunk;
      chunk.read( iter, end );

      IncidentParticle copy( chunk );

      THEN( "an IncidentParticle can be constructed and members can be tested" ) {

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

      auto iter = record.begin() + 8;
      auto end = record.end();
      IncidentParticle chunk;
      chunk.read( iter, end );

      IncidentParticle move( std::move( chunk ) );

      THEN( "an IncidentParticle can be move constructed and members can be tested" ) {

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

      auto iter = record.begin() + 8;
      auto end = record.end();
      IncidentParticle chunk;
      chunk.read( iter, end );

      IncidentParticle copy = makeDummyRecord();
      copy = chunk;

      THEN( "an IncidentParticle can be copy assigned and members can be tested" ) {

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

      auto iter = record.begin() + 8;
      auto end = record.end();
      IncidentParticle chunk;
      chunk.read( iter, end );

      IncidentParticle move = makeDummyRecord();
      move = std::move( chunk );

      THEN( "an IncidentParticle can be move assigned and members can be tested" ) {

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

  GIVEN( "invalid data for an IncidentParticle instance" ) {

    WHEN( "the number of targets is insufficient" ) {

      std::vector< Target > targets = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( IncidentParticle( 1, std::move( targets ) ) );
      } // THEN
    } // WHEN

    WHEN( "reading the data of the record and the number of targets "
          "values is insufficient" ) {

      std::string record = chunkWithInsufficientNumberTargets();
      auto iter = record.begin() + 8;
      auto end = record.end();
      Target chunk;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( chunk.read( iter, end) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const IncidentParticle& chunk ) {

  CHECK( "inc_part" == chunk.keyword() );
  CHECK(          1 == chunk.incidentIdentifier() );
  CHECK(          2 == chunk.numberTargets() );

  CHECK( "target" == chunk.targets()[0].keyword() );
  CHECK(     1001 == chunk.targets()[0].targetIdentifier() );
  CHECK(        1 == chunk.targets()[0].numberProducts() );
  CHECK(     1002 == chunk.targets()[0].products()[0].reactionProduct() );
  CHECK(        1 == chunk.targets()[0].products()[0].numberReactions() );
  CHECK(      102 == chunk.targets()[0].products()[0].reactionIdentifiers()[0] );
  CHECK(        1 == chunk.targets()[0].products()[0].multiplicities()[0] );

  CHECK( "target" == chunk.targets()[1].keyword() );
  CHECK(     1002 == chunk.targets()[1].targetIdentifier() );
  CHECK(        2 == chunk.targets()[1].numberProducts() );
  CHECK(     1001 == chunk.targets()[1].products()[0].reactionProduct() );
  CHECK(        1 == chunk.targets()[1].products()[0].numberReactions() );
  CHECK(       16 == chunk.targets()[1].products()[0].reactionIdentifiers()[0] );
  CHECK(        1 == chunk.targets()[1].products()[0].multiplicities()[0] );
  CHECK(     1003 == chunk.targets()[1].products()[1].reactionProduct() );
  CHECK(        1 == chunk.targets()[1].products()[1].numberReactions() );
  CHECK(      102 == chunk.targets()[1].products()[1].reactionIdentifiers()[0] );
  CHECK(        1 == chunk.targets()[1].products()[1].multiplicities()[0] );
}

std::string chunk() {

 return "inc_part\n"
        "  1\n"
//        "\n"
        "  num_targets\n"
        "    2\n"
//        "\n"
        "  target\n"
        "    1001\n"
        "    num_products\n"
        "      1\n"
        "    product\n"
        "      1002\n"
        "      1\n"
        "      102 1\n"
//        "\n"
        "  target\n"
        "    1002\n"
        "    num_products\n"
        "      2\n"
        "    product\n"
        "      1001\n"
        "      1\n"
        "      16 1\n"
        "    product\n"
        "      1003\n"
        "      1\n"
        "      102 1\n";
}

std::string chunkWithInsufficientNumberTargets() {

  return "inc_part\n";
}

IncidentParticle makeDummyRecord() {

  std::vector< Target > targets = {
      Target(1001, { Product({1002, {102}, {1}}) }),
      Target(1002, { Product({1001, {16}, {1}}), Product({1003, {102}, {1}}) })
  };

  IncidentParticle chunk( 1, targets );

  return chunk;
}
