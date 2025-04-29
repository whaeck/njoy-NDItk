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
  )
  .def_property_readonly(

    "number_tables",
    [] (const Library& self) -> decltype(auto) {
      return self.numberTables();
    },
    "Return the number of data tables in the library"
  )
  .def_property_readonly(

    "header",
    [] (const Library& self) -> decltype(auto) {
      return self.header();
    },
    "Return the header in the library"
  )
  .def_property_readonly(

    "tables",
    [] (const Library& self) -> decltype(auto) {
      return self.tables();
    },
    "Return a vector of tables in the library"
  )
  .def(

    "get_table",
    [] (const Library& self, const std::string& zaid) -> decltype(auto) {
      return self.getTable(zaid);
    },
    python::arg( "zaid" ),
    "Return the table in the library with the associated zaid\n\n"
    "Arguments:\n"
    "    self       the library\n"
    "    zaid       the zaid string of the table in the library file"
  )
  .def(

    "has_table",
    [] (const Library& self, const std::string& zaid) -> decltype(auto) {
      return self.hasTable(zaid);
    },
    python::arg( "zaid" ),
    "Check if there is a table in the library with the associated zaid\n\n"
    "Arguments:\n"
    "    self       the library\n"
    "    zaid       the zaid string of the table in the library file"
  );

  // add standard table definitions
  addStandardTableDefinitions< Library >( library );
}
