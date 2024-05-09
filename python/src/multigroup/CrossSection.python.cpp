// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "NDItk/multigroup/CrossSection.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace multigroup {

void wrapCrossSection( python::module& module, python::module& ) {

  // type aliases
  using Record = njoy::NDItk::multigroup::CrossSection;

  // wrap views created by this record

  // create the record
  python::class_< Record > record(

    module,
    "CrossSection",
    "A cross section subrecord for multigroup neutron and photon data"
  );

  // wrap the record
  record
  .def(

    python::init< int, double, std::vector< double > >(),
    python::arg( "reaction" ), python::arg( "qvalue" ),
    python::arg( "values" ),
    "Initialise the subrecord\n\n"
    "Arguments:\n"
    "    self       the record\n"
    "    reaction   the reaction number\n"
    "    qvalue     the q value\n"
    "    values     the cross section values"
  )
  .def_property_readonly(

    "identifier",
    &Record::identifier,
    "The reaction identifier"
  )
  .def_property_readonly(

    "qvalue",
    &Record::qvalue,
    "The reaction Q value"
  )
  .def_property_readonly(

    "cross_sections",
    [] ( const Record& self ) -> DoubleRange
       { return self.crossSections(); },
    "The cross section values"
  )
  .def_property_readonly(

    "number_groups",
    &Record::numberGroups,
    "The number of groups defined by this record"
  );

  // add standard record definitions
  addStandardSubrecordDefinitions< Record, DoubleRange >( record );
}

} // multigroup namespace
