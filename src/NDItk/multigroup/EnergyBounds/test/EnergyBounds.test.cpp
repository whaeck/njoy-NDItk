// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "NDItk/multigroup/EnergyBounds.hpp"

// other includes
#include <sstream>
// convenience typedefs
using namespace njoy::NDItk;
std::string chunk();
void verifychunk(const multigroup::EnergyBounds&);

SCENARIO( "EnergyBounds" ) {
  std:: string line = chunk();
  GIVEN( "Given Energy Bounds" ) {
    
    WHEN( "the data is given explicitly" ) {

      std::vector< double > energies = { 10, 1, 1E-2, 1E-5 };

      multigroup::EnergyBounds chunk( std::move( energies ) );

      THEN( "an EnergyBounds can be constructed and members can be tested" ) {
    
      verifychunk(chunk);
      } // THEN
      THEN( "an EnergyBounds can be written" ) {
        std::ostringstream out;
       chunk.write(out);

      CHECK(out.str()==line);
      }
     
    } // WHEN
     WHEN( "the data is read from a stream" ) {

      std::istringstream in(chunk());

      multigroup::EnergyBounds chunk(in, 4);

      THEN( "an EnergyBounds can be constructed and members can be tested" ) {
        verifychunk(chunk);

      } // THEN

     
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk()
{
 return "e_bounds 10 1 0.01 1e-05\n";
}
void verifychunk(const multigroup::EnergyBounds& chunk )
{
        CHECK ( "e_bounds" == chunk.name()); 
        CHECK ( 3 == chunk.numberGroups());
        CHECK_THAT(10, WithinRel(chunk.bounds()[0]));
        CHECK_THAT(1, WithinRel(chunk.bounds()[1]));
        CHECK_THAT(1E-2, WithinRel(chunk.bounds()[2]));
        CHECK_THAT(1E-5, WithinRel(chunk.bounds()[3]));
}

