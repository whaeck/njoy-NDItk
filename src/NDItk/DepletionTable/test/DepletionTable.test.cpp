// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/DepletionTable.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;

using IncidentParticle = depletion::IncidentParticle;
using Target           = depletion::Target;
using Product          = depletion::Product;

std::string chunk();
void verifyChunk( const DepletionTable& );
std::string chunkWithMissingRecords();

SCENARIO( "DepletionTable" ) {

  GIVEN( "valid data for a DepletionTable instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      std::string zaid = "nosub.010zpd";
      std::string information = "this is some information for the table";
      std::string name = "e66_618_chain";
      std::string source = "02/01/2007";
      std::string process = "02/01/2007";
      
      std::vector< IncidentParticle > incident = {

        { 1, { Target(1001, { Product({1002, {102}, {1}}) }),
               Target(1002, { Product({1001, {16}, {1}}), Product({1003, {102}, {1}}) }) } }
      };

      DepletionTable chunk( std::move( zaid ), 
                            std::move( name ),
                            std::move( process ), 
                            std::move( incident ),
                            std::move( information ), 
                            std::move( source ) );

      THEN( "a DepletionTable can be constructed and members can "
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

      auto iter = record.begin();
      auto end = record.end();

      DepletionTable chunk;
      chunk.read( iter, end );

      THEN( "a DepletionTable can be constructed and members can "
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

  GIVEN( "invalid data for a DepletionTable instance" ) {

    WHEN( "required records are missing" ) {

      std::string record = chunkWithMissingRecords();
      auto iter = record.begin();
      auto end = record.end();

      DepletionTable chunk;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( chunk.read( iter, end ) );
      } // THEN
    } // WHEN

  } // GIVEN
} // SCENARIO

std::string chunk() {

  return "zaid\n"
         "    nosub.010zpd\n"
//       "\n"
         "info\n"
         "    this is some information for the table\n"
//       "\n"
         "library_name\n"
         "    e66_618_chain\n"
//       "\n"
         "date_source\n"
         "    02/01/2007\n"
//       "\n"
         "date_processed\n"
         "    02/01/2007\n"
//       "\n"
         "num_inc_parts\n"
         "    1\n"
//       "\n"
         "inc_part\n"
         "  1\n"
//       "\n"
         "  num_targets\n"
         "    2\n"
//       "\n"
         "  target\n"
         "    1001\n"
         "    num_products\n"
         "      1\n"
         "    product\n"
         "      1002\n"
         "      1\n"
         "      102 1\n"
//       "\n"
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
         "      102 1\n"
//       "\n"
         "end\n";
}

void verifyChunk( const DepletionTable& chunk ) {

  CHECK( 1 == chunk.numberIncidentParticles() );

  auto metadata = chunk.metadata();
  CHECK( "nosub.010zpd" == metadata.zaid() );
  CHECK( "this is some information for the table" == metadata.information() );
  CHECK( "e66_618_chain" == metadata.libraryName() );
  CHECK( "02/01/2007" == metadata.sourceDate() );
  CHECK( "02/01/2007" == metadata.processingDate() );

  auto incident0 = chunk.incidentParticles()[0];
  CHECK( 1 == chunk.incidentParticle(1).incidentIdentifier() );
  CHECK( "inc_part" == incident0.keyword() );
  CHECK(          1 == incident0.incidentIdentifier() );
  CHECK(          2 == incident0.numberTargets() );

  auto target0 = incident0.targets()[0];
  CHECK( "target" == target0.keyword() );
  CHECK(     1001 == target0.targetIdentifier() );
  CHECK(        1 == target0.numberProducts() );
  CHECK(     1002 == target0.products()[0].reactionProduct() );
  CHECK(        1 == target0.products()[0].numberReactions() );
  CHECK(      102 == target0.products()[0].reactionIdentifiers()[0] );
  CHECK(        1 == target0.products()[0].multiplicities()[0] );

  auto target1 = incident0.targets()[1];
  CHECK( "target" == target1.keyword() );
  CHECK(     1002 == target1.targetIdentifier() );
  CHECK(        2 == target1.numberProducts() );
  CHECK(     1001 == target1.products()[0].reactionProduct() );
  CHECK(        1 == target1.products()[0].numberReactions() );
  CHECK(       16 == target1.products()[0].reactionIdentifiers()[0] );
  CHECK(        1 == target1.products()[0].multiplicities()[0] );
  CHECK(     1003 == target1.products()[1].reactionProduct() );
  CHECK(        1 == target1.products()[1].numberReactions() );
  CHECK(      102 == target1.products()[1].reactionIdentifiers()[0] );
  CHECK(        1 == target1.products()[1].multiplicities()[0] );
}

std::string chunkWithMissingRecords() {

  return "zaid\n"
         "    nosub.010zpd\n"
//       "\n"
         "info\n"
         "    this is some information for the table\n"
//       "\n"
         "library_name\n"
         "    e66_618_chain\n"
//       "\n"
         "date_source\n"
         "    02/01/2007\n"
//       "\n"
         "date_processed\n"
         "    02/01/2007\n"
//       "\n"
         "end\n";
}
