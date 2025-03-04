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

  // metadata
  CHECK( "nosub.010zpd" == chunk.metadata().zaid() );
  CHECK( "this is some information for the table" == chunk.metadata().information() );
  CHECK( "e66_618_chain" == chunk.metadata().libraryName() );
  CHECK( "02/01/2007" == chunk.metadata().sourceDate() );
  CHECK( "02/01/2007" == chunk.metadata().processingDate() );

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
