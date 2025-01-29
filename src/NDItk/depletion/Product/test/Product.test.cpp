// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/depletion/Product.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using Product = depletion::Product;

std::string chunk();
std::vector< int > data();
void verifyChunk( const Product& );
std::vector< int > dataWithInsufficientLength();

SCENARIO( "Product" ) {

  GIVEN( "valid data for a Product instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      int product = 1001;
      std::vector< int > reactions = { 28, 45, 103, 111, 112 };
      std::vector< int > multiplicities = { 1, 1, 1, 2, 1 };

      Product chunk( product, std::move( reactions ), std::move( multiplicities ) );

      THEN( "a Product can be constructed and members can "
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

      std::vector< int > values = data();
      auto begin = values.begin();
      auto end = values.end();

      Product chunk( begin, end );

      THEN( "a Product can be constructed and members can "
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

  GIVEN( "invalid data for a Product instance" ) {

    WHEN( "the number of reaction identifiers and multiplcities is insufficient" ) {

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( Product( 1001, { 28, 45 }, { 1 } ) );
      } // THEN
    } // WHEN

    WHEN( "using iterators and the number of data values is "
          "insufficient" ) {

      std::vector< int > values = dataWithInsufficientLength();
      auto begin = values.begin();
      auto end = values.end();

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( Product( begin, end ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return "    1001\n"
         "    5\n"
         "    28 1\n"
         "    45 1\n"
         "    103 1\n"
         "    111 2\n"
         "    112 1\n";
}

std::vector< int > data() {

  return { 1001,
           5,
           28, 1, 45, 1, 103, 1, 111, 2, 112, 1 };
}

void verifyChunk( const Product& chunk ) {

  CHECK( 1001 == chunk.values()[0]  );
  CHECK( 5    == chunk.values()[1]  );
  CHECK( 28   == chunk.values()[2]  );
  CHECK( 1    == chunk.values()[3]  );
  CHECK( 45   == chunk.values()[4]  );
  CHECK( 1    == chunk.values()[5]  );
  CHECK( 103  == chunk.values()[6]  );
  CHECK( 1    == chunk.values()[7]  );
  CHECK( 111  == chunk.values()[8]  );
  CHECK( 2    == chunk.values()[9]  );
  CHECK( 112  == chunk.values()[10] );
  CHECK( 1    == chunk.values()[11] );

  CHECK( false == chunk.empty() );
  CHECK( 12 == chunk.size() );

  CHECK( 5    == chunk.numberReactions() );
  CHECK( 5    == chunk.reactionIdentifiers().size() );
  CHECK( 5    == chunk.multiplicities().size() );
  CHECK( 1001 == chunk.reactionProduct() );
  CHECK( 28   == chunk.reactionIdentifiers()[0] );
  CHECK( 45   == chunk.reactionIdentifiers()[1] );
  CHECK( 103  == chunk.reactionIdentifiers()[2] );
  CHECK( 111  == chunk.reactionIdentifiers()[3] );
  CHECK( 112  == chunk.reactionIdentifiers()[4] );
  CHECK( 1    == chunk.multiplicities()[0] );
  CHECK( 1    == chunk.multiplicities()[1] );
  CHECK( 1    == chunk.multiplicities()[2] );
  CHECK( 2    == chunk.multiplicities()[3] );
  CHECK( 1    == chunk.multiplicities()[4] );
}

std::vector< int > dataWithInsufficientLength() {

  return { 16 };
}
