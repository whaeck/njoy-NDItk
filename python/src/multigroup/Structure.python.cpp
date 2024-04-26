// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "NDItk/multigroup/Structure.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"
#include "read.hpp"

// namespace aliases
namespace python = pybind11;

namespace multigroup {

void wrapStructure( python::module& module, python::module& ) {

  // type aliases
  using Record = njoy::NDItk::multigroup::Structure;

  // wrap views created by this record

  // create the record
  python::class_< Record > record(

    module,
    "Structure",
    "A group structure record for multigroup neutron and photon data"
  );

  // wrap the record
  record
  .def(

    python::init< std::vector< double > >(),
    python::arg( "boundaries" ),
    "Initialise the table\n\n"
    "Arguments:\n"
    "    self          the table\n"
    "    boundaries    the group structure boundaries"
  )
  .def_property_readonly(

    "boundaries",
    [] ( const Record& self ) -> DoubleRange
       { return self.boundaries(); },
    "The group structure boundaries"
  )
  .def_property_readonly(

    "number_groups",
    &Record::numberGroups,
    "The number of groups defined by this record"
  )
  .def_static(

    "from_string",
    [] ( const std::string& string, std::size_t number ) -> Record
       { return read< Record >( string, number ); },
    python::arg( "string" ), python::arg( "number" ),
    "Read the record from a string\n\n"
    "An exception is raised if something goes wrong while reading the\n"
    "component\n\n"
    "Arguments:\n"
    "    string    the string representing the component\n"
    "    number    the number of boundary values to be read"
  );

  // add standard record definitions
  addStandardRecordDefinitions< Record, DoubleRange >( record );
}

} // multigroup namespace
