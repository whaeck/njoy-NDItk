// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "NDItk/depletion/IncidentParticle.hpp"
#include "NDItk/depletion/Target.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"
#include "read.hpp"

// namespace aliases
namespace python = pybind11;

namespace depletion {

void wrapIncidentParticle( python::module& module, python::module& ) {

  // type aliases
  using Record  = njoy::NDItk::depletion::IncidentParticle;
  using Target  = njoy::NDItk::depletion::Target;

  // wrap views created by this record

  // create the record
  python::class_< Record > record(

    module,
    "IncidentParticle",
    "An incident particle record for depletion data"
  );

  // wrap the record
  record
  .def(

    python::init< int, std::vector< Target > >(),
    python::arg( "identifier" ),
    python::arg( "targets" ),
    "Initialise the record\n\n"
    "Arguments:\n"
    "    self              the record\n"
    "    identifier        the target particle identifier"
    "    targets           a vector of depletion targets"
  )
  .def_property_readonly(

    "incident_identifier",
    &Record::incidentIdentifier,
    "Return the target particle identifier"
  )
  .def_property_readonly(

    "number_targets",
    &Record::numberTargets,
    "Return the number of targets for this incident particle"
  )
  .def_property_readonly(

    "targets",
    &Record::targets,
    "Return the target data for this incident particle"
  );

  // add standard record definitions
  addBaseRecordDefinitions<Record>( record );
}

} // depletion namespace
