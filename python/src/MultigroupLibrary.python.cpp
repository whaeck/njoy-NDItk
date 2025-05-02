// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "NDItk/MultigroupTable.hpp"
#include "NDItk/MultigroupLibrary.hpp"
#include "definitions.hpp"
#include "read.hpp"

// namespace aliases
namespace python = pybind11;

void wrapMultigroupLibrary( python::module& module, python::module& ) {

  // type aliases
  using Table = njoy::NDItk::MultigroupTable;
  using Library = njoy::NDItk::MultigroupLibrary;

  // wrap views created by this table

  // create the table
  python::class_< Library > library(

    module,
    "MultigroupLibrary",
    "A library containing multigroup tables"
  );

  // wrap the table
  library
  .def(

    python::init< 
      std::string, 
      std::vector< Table > >(),
    python::arg( "header" ), 
    python::arg( "tables" ),
    "Initialise the library\n\n"
    "Arguments:\n"
    "    self               the library\n"
    "    header             the string header of the library\n"
    "    tables             a vector of MultigroupTable\n"
  );

  // add standard table definitions
  addStandardLibraryDefinitions< Library >( library );
}
