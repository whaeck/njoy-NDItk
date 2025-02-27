// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/depletion/Target.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using Product = depletion::Product;
using Target  = depletion::Target;

std::string chunk();
void verifyChunk( const Target& );
std::string chunkWithInsufficientNumberProducts();
Target makeDummyRecord();

SCENARIO( "Target" ) {

  GIVEN( "valid data for a Target instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< Product > products = {

        {{ 1001, { 24, 103 }, { 1, 1 } }},
        {{ 1002, { 32 }, { 1 } }},
        {{ 1003, { 105 }, { 1 } }},
        {{ 2004, { 24, 32, 105 }, { 1, 1, 1 } }},
        {{ 2006, { 103 }, { 1 } }},
        {{ 3007, { 102 }, { 1 } }}
      };

      Target chunk( 3006, std::move( products ) );

      THEN( "a Target can be constructed and members can be tested" ) {

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

      Target chunk;
      chunk.read( iter, end );

      THEN( "a Target can be constructed and members can be tested" ) {

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
      Target chunk;
      chunk.read( iter, end );

      Target copy( chunk );

      THEN( "a Target can be constructed and members can be tested" ) {

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
      Target chunk;
      chunk.read( iter, end );

      Target move( std::move( chunk ) );

      THEN( "a Target can be move constructed and members can be tested" ) {

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
      Target chunk;
      chunk.read( iter, end );

      Target copy = makeDummyRecord();
      copy = chunk;

      THEN( "a Target can be copy assigned and members can be tested" ) {

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
      Target chunk;
      chunk.read( iter, end );

      Target move = makeDummyRecord();
      move = std::move( chunk );

      THEN( "a Target can be move assigned and members can be tested" ) {

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

/*
  GIVEN( "invalid data for a Target instance" ) {

    WHEN( "the number of products is insufficient" ) {

      std::vector< Product > products = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( Target( 3006, std::move( products ) ) );
      } // THEN
    } // WHEN

    WHEN( "reading the data of the record and the number of products "
          "values is insufficient" ) {

      std::string record = chunkWithInsufficientNumberProducts();
      auto iter = record.begin() + 6;
      auto end = record.end();
      Target chunk;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( chunk.read( iter, end) );
      } // THEN
    } // WHEN
  } // GIVEN
*/
} // SCENARIO

void verifyChunk( const Target& chunk ) {

  CHECK( "target" == chunk.keyword() );
  CHECK( 3006 == chunk.targetIdentifier() );
  CHECK(    6 == chunk.numberProducts() );

  CHECK( 1001 == chunk.products()[0].reactionProduct() );
  CHECK(    2 == chunk.products()[0].numberReactions() );
  CHECK(   24 == chunk.products()[0].reactionIdentifiers()[0] );
  CHECK(  103 == chunk.products()[0].reactionIdentifiers()[1] );
  CHECK(    1 == chunk.products()[0].multiplicities()[0] );
  CHECK(    1 == chunk.products()[0].multiplicities()[1] );

  CHECK( 1002 == chunk.products()[1].reactionProduct() );
  CHECK(    1 == chunk.products()[1].numberReactions() );
  CHECK(   32 == chunk.products()[1].reactionIdentifiers()[0] );
  CHECK(    1 == chunk.products()[1].multiplicities()[0] );

  CHECK( 1003 == chunk.products()[2].reactionProduct() );
  CHECK(    1 == chunk.products()[2].numberReactions() );
  CHECK(  105 == chunk.products()[2].reactionIdentifiers()[0] );
  CHECK(    1 == chunk.products()[2].multiplicities()[0] );

  CHECK( 2004 == chunk.products()[3].reactionProduct() );
  CHECK(    3 == chunk.products()[3].numberReactions() );
  CHECK(   24 == chunk.products()[3].reactionIdentifiers()[0] );
  CHECK(   32 == chunk.products()[3].reactionIdentifiers()[1] );
  CHECK(  105 == chunk.products()[3].reactionIdentifiers()[2] );
  CHECK(    1 == chunk.products()[3].multiplicities()[0] );
  CHECK(    1 == chunk.products()[3].multiplicities()[1] );
  CHECK(    1 == chunk.products()[3].multiplicities()[2] );

  CHECK( 2006 == chunk.products()[4].reactionProduct() );
  CHECK(    1 == chunk.products()[4].numberReactions() );
  CHECK(  103 == chunk.products()[4].reactionIdentifiers()[0] );
  CHECK(    1 == chunk.products()[4].multiplicities()[0] );

  CHECK( 3007 == chunk.products()[5].reactionProduct() );
  CHECK(    1 == chunk.products()[5].numberReactions() );
  CHECK(  102 == chunk.products()[5].reactionIdentifiers()[0] );
  CHECK(    1 == chunk.products()[5].multiplicities()[0] );
}

std::string chunk() {

  return "  target\n"
         "    3006\n"
         "    num_products\n"
         "      6\n"
         "    product\n"
         "      1001\n"
         "      2\n"
         "      24 1\n"
         "      103 1\n"
         "    product\n"
         "      1002\n"
         "      1\n"
         "      32 1\n"
         "    product\n"
         "      1003\n"
         "      1\n"
         "      105 1\n"
         "    product\n"
         "      2004\n"
         "      3\n"
         "      24 1\n"
         "      32 1\n"
         "      105 1\n"
         "    product\n"
         "      2006\n"
         "      1\n"
         "      103 1\n"
         "    product\n"
         "      3007\n"
         "      1\n"
         "      102 1\n";
}

std::string chunkWithInsufficientNumberProducts() {

  return "target\n";
}

Target makeDummyRecord() {

  return Target( 1001, { {{ 1002, { 102 }, { 1 } }} } );
}
