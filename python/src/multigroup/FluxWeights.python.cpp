// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "NDItk/multigroup/FluxWeights.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace multigroup {

void wrapFluxWeights( python::module& module, python::module& ) {

  // type aliases
  using Record = njoy::NDItk::multigroup::FluxWeights;

  // wrap views created by this record

  // create the record
  python::class_< Record > record(

    module,
    "FluxWeights",
    "A flux weight record for multigroup neutron and photon data"
  );

  // wrap the record
  record
  .def(

    python::init< std::vector< double > >(),
    python::arg( "weights" ),
    "Initialise the table\n\n"
    "Arguments:\n"
    "    self       the table\n"
    "    weights    the flux weights"
  )
  .def_property_readonly(

    "weights",
    [] ( const Record& self ) -> DoubleRange
       { return self.weights(); },
    "The flux weights"
  )
  .def_property_readonly(

    "number_groups",
    &Record::numberGroups,
    "The number of groups defined by this record"
  );

  // add standard record definitions
  addStandardRecordDefinitions< Record, DoubleRange >( record );
}

} // multigroup namespace
