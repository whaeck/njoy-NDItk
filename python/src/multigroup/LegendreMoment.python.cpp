// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "NDItk/multigroup/LegendreMoment.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace multigroup {

void wrapLegendreMoment( python::module& module, python::module& ) {

  // type aliases
  using Record = njoy::NDItk::multigroup::LegendreMoment;

  // wrap views created by this record

  // create the record
  python::class_< Record > record(

    module,
    "LegendreMoment",
    "A Legendre moment subrecord for multigroup neutron and photon data"
  );

  // wrap the record
  record
  .def(

    python::init< int, std::vector< double >, unsigned int >(),
    python::arg( "order" ), python::arg( "values" ),
    python::arg( "incident" ),
    "Initialise the subrecord\n\n"
    "Arguments:\n"
    "    self        the record\n"
    "    order       the Legendre order\n"
    "    values      the values of the matrix\n"
    "    incident    the number of primary groups"
  )
  .def(

    python::init< int, std::vector< double >, unsigned int, unsigned int >(),
    python::arg( "order" ), python::arg( "values" ),
    python::arg( "incident" ), python::arg( "outgoing" ),
    "Initialise the subrecord\n\n"
    "Arguments:\n"
    "    self        the record\n"
    "    order       the Legendre order\n"
    "    values      the values of the matrix\n"
    "    incident    the number of primary groups\n"
    "    outgoing    the number of outgoing groups"
  )
  .def_property_readonly(

    "order",
    &Record::order,
    "The Legendre moment order"
  )
  .def_property_readonly(

    "number_primary_groups",
    &Record::numberPrimaryGroups,
    "The number of incident groups"
  )
  .def_property_readonly(

    "number_outgoing_groups",
    &Record::numberOutgoingGroups,
    "The number of outgoing groups"
  )
  .def_property_readonly(

    "matrix",
    [] ( const Record& self ) -> DoubleRange2D
       { return self.matrix(); },
    "The matrix defined by this subrecord"
  );

  // add standard record definitions
  addStandardSubrecordDefinitions< Record, DoubleRange >( record );
}

} // multigroup namespace
