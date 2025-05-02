// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/DepletionTable.hpp"
#include "NDItk/DepletionLibrary.hpp"

// other includes
#include <type_traits>

// convenience typedefs
using namespace njoy::NDItk;
using Library = njoy::NDItk::DepletionLibrary;

std::string chunk();
void verifyChunk( const DepletionLibrary& );
void verifySubChunk1( const DepletionTable& );
void verifySubChunk2( const DepletionTable& );
void verifySubChunk3( const DepletionTable& );

SCENARIO( "DepletionLibrary" ) {

  GIVEN( "valid data for a DepletionLibrary instance" ) {

    std::string record = chunk();

    WHEN( "the data is read using iterators" ) {

      auto iter = record.begin();
      auto end = record.end();

      DepletionLibrary chunk;
      chunk.read( iter, end );

      THEN( "a DepletionLibrary can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "the DepletionLibrary record can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output );

        CHECK( buffer == record );
      } // THEN
    } // WHEN
  } // GIVEN

} // SCENARIO

std::string chunk() {

  return "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.\n"
         "Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\n"
         "Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.\n"
         "Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.\n"
         "\n"
         "zaid\n"
         "    test_zaid_1\n"
         "info\n"
         "    this is some information for the table\n"
         "library_name\n"
         "    e66_618_chain\n"
         "date_source\n"
         "    02/01/2007\n"
         "date_processed\n"
         "    02/01/2007\n"
         "num_inc_parts\n"
         "    1\n"
         "inc_part\n"
         "  1\n"
         "  num_targets\n"
         "    1\n"
         "  target\n"
         "    1001\n"
         "    num_products\n"
         "      1\n"
         "    product\n"
         "      1002\n"
         "      1\n"
         "      102 1\n"
         "end\n"
         "\n"
         "zaid\n"
         "    test_zaid_2\n"
         "info\n"
         "    this is some information for the table\n"
         "library_name\n"
         "    e66_618_chain\n"
         "date_source\n"
         "    02/01/2007\n"
         "date_processed\n"
         "    02/01/2007\n"
         "num_inc_parts\n"
         "    1\n"
         "inc_part\n"
         "  1\n"
         "  num_targets\n"
         "    1\n"
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
         "end\n"
         "\n"
         "zaid\n"
         "    test_zaid_3\n"
         "info\n"
         "    this is some information for the table\n"
         "library_name\n"
         "    e66_618_chain\n"
         "date_source\n"
         "    02/01/2007\n"
         "date_processed\n"
         "    02/01/2007\n"
         "num_inc_parts\n"
         "    1\n"
         "inc_part\n"
         "  1\n"
         "  num_targets\n"
         "    2\n"
         "  target\n"
         "    1001\n"
         "    num_products\n"
         "      1\n"
         "    product\n"
         "      1002\n"
         "      1\n"
         "      102 1\n"
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
         "end\n";
}

void verifySubChunk1( const DepletionTable& chunk ) {

  CHECK( 1 == chunk.numberIncidentParticles() );

  auto metadata = chunk.metadata();
  CHECK( "test_zaid_1" == metadata.zaid() );
  CHECK( "this is some information for the table" == metadata.information() );
  CHECK( "e66_618_chain" == metadata.libraryName() );
  CHECK( "02/01/2007" == metadata.sourceDate() );
  CHECK( "02/01/2007" == metadata.processingDate() );

  auto incident0 = chunk.incidentParticles()[0];
  CHECK( 1 == chunk.incidentParticle(1).incidentIdentifier() );
  CHECK( "inc_part" == incident0.keyword() );
  CHECK(          1 == incident0.incidentIdentifier() );
  CHECK(          1 == incident0.numberTargets() );

  auto target0 = incident0.targets()[0];
  CHECK( "target" == target0.keyword() );
  CHECK(     1001 == target0.targetIdentifier() );
  CHECK(        1 == target0.numberProducts() );
  CHECK(     1002 == target0.products()[0].reactionProduct() );
  CHECK(        1 == target0.products()[0].numberReactions() );
  CHECK(      102 == target0.products()[0].reactionIdentifiers()[0] );
  CHECK(        1 == target0.products()[0].multiplicities()[0] );
}

void verifySubChunk2( const DepletionTable& chunk ) {

  CHECK( 1 == chunk.numberIncidentParticles() );

  auto metadata = chunk.metadata();
  CHECK( "test_zaid_2" == metadata.zaid() );
  CHECK( "this is some information for the table" == metadata.information() );
  CHECK( "e66_618_chain" == metadata.libraryName() );
  CHECK( "02/01/2007" == metadata.sourceDate() );
  CHECK( "02/01/2007" == metadata.processingDate() );

  auto incident0 = chunk.incidentParticles()[0];
  CHECK( 1 == chunk.incidentParticle(1).incidentIdentifier() );
  CHECK( "inc_part" == incident0.keyword() );
  CHECK(          1 == incident0.incidentIdentifier() );
  CHECK(          1 == incident0.numberTargets() );

  auto target1 = incident0.targets()[0];
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

void verifySubChunk3( const DepletionTable& chunk ) {

  CHECK( 1 == chunk.numberIncidentParticles() );

  auto metadata = chunk.metadata();
  CHECK( "test_zaid_3" == metadata.zaid() );
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

void verifyChunk( const DepletionLibrary& chunk ) {
  std::string header( 
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.\n"
    "Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\n"
    "Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.\n"
    "Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.\n"
  );

  CHECK( chunk.numberTables() == 3 );
  CHECK( std::is_same_v< decltype(chunk.tables()), const std::vector<DepletionTable>& > );
  CHECK( chunk.hasTable("test_zaid_1") );
  CHECK( chunk.hasTable("test_zaid_2") );
  CHECK( chunk.hasTable("test_zaid_3") );
  CHECK( not chunk.hasTable("asdf") );
  CHECK( chunk.header() == header );
  verifySubChunk1( chunk.getTable("test_zaid_1") );
  verifySubChunk2( chunk.getTable("test_zaid_2") );
  verifySubChunk3( chunk.getTable("test_zaid_3") );
  verifySubChunk1( chunk.getTable(0) );
  verifySubChunk2( chunk.getTable(1) );
  verifySubChunk3( chunk.getTable(2) );
}