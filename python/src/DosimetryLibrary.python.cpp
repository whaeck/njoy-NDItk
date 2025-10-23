// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "NDItk/DosimetryTable.hpp"
#include "NDItk/DosimetryLibrary.hpp"
#include "definitions.hpp"
#include "read.hpp"

// namespace aliases
namespace python = pybind11;

void wrapDosimetryLibrary( python::module& module, python::module& ) {

  // type aliases
  using Table = njoy::NDItk::DosimetryTable;
  using Library = njoy::NDItk::DosimetryLibrary;

  // wrap views created by this table

  // create the table
  python::class_< Library > library(

    module,
    "DosimetryLibrary",
    "A library containing dosimetry tables"
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
    "    tables             a vector of DosimetryTable\n"
  );

  // add standard library definitions
  addStandardLibraryDefinitions< Library >( library );
}
