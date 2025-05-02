// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "NDItk/DepletionTable.hpp"
#include "NDItk/DepletionLibrary.hpp"
#include "definitions.hpp"
#include "read.hpp"

// namespace aliases
namespace python = pybind11;

void wrapDepletionLibrary( python::module& module, python::module& ) {

  // type aliases
  using Table = njoy::NDItk::DepletionTable;
  using Library = njoy::NDItk::DepletionLibrary;

  // wrap views created by this table

  // create the table
  python::class_< Library > library(

    module,
    "DepletionLibrary",
    "A library containing depletion tables"
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
    "    tables             a vector of DepletionTable\n"
  );

  // add standard library definitions
  addStandardLibraryDefinitions< Library >( library );
}
