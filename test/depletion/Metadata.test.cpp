// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/depletion/Metadata.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using Metadata = depletion::Metadata;

std::string chunk();
void verifyChunk( const Metadata& );

SCENARIO( "Metadata" ) {

  GIVEN( "valid data for a Metadata instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      std::string zaid = "nosub.010zpd";
      std::string name = "e66_618_chain";
      std::optional< std::string > information = "this is some information for the table";
      std::optional< std::string > source = "12/22/2011";
      std::string process = "08/07/2013";
      unsigned int incident = 1;

      Metadata chunk( 
        std::move( zaid ), 
        std::move( name ), 
        std::move( process ), 
        incident,
        std::move( information ),
        std::move( source ) 
      );

      THEN( "a Metadata can be constructed and members can "
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

      auto readKey = [] ( auto&& iter, auto&& end ) {

        return njoy::tools::disco::FreeFormatCharacter::read< std::string >( iter, end );
      };

      Metadata chunk;
      chunk.read( readKey( iter, end ), iter, end );
      chunk.read( readKey( iter, end ), iter, end );
      chunk.read( readKey( iter, end ), iter, end );
      chunk.read( readKey( iter, end ), iter, end );
      chunk.read( readKey( iter, end ), iter, end );
      chunk.read( readKey( iter, end ), iter, end );

      THEN( "a Metadata can be constructed and members can "
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

  return "zaid\n"
         "    nosub.010zpd\n"
         "info\n"
         "    this is some information for the table\n"
         "library_name\n"
         "    e66_618_chain\n"
         "date_source\n"
         "    12/22/2011\n"
         "date_processed\n"
         "    08/07/2013\n"
         "num_inc_parts\n"
         "    1\n";
}

void verifyChunk( const Metadata& chunk ) {

  CHECK( "nosub.010zpd" == chunk.zaid() );
  CHECK( "this is some information for the table" == chunk.information() );
  CHECK( "e66_618_chain" == chunk.libraryName() );
  CHECK( "12/22/2011" == chunk.sourceDate() );
  CHECK( "08/07/2013" == chunk.processingDate() );
  CHECK(   1 == chunk.numberIncidentParticles() );
}
