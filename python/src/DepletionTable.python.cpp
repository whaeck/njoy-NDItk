// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "NDItk/DepletionTable.hpp"
#include "definitions.hpp"
#include "read.hpp"

// namespace aliases
namespace python = pybind11;

void wrapDepletionTable( python::module& module, python::module& ) {

  // type aliases
  using Table = njoy::NDItk::DepletionTable;
  using IncidentParticle = njoy::NDItk::depletion::IncidentParticle;

  // wrap views created by this table

  // create the table
  python::class_< Table > table(

    module,
    "DepletionTable",
    "A production/depletion table"
  );

  // wrap the table
  table
  .def(

    python::init< 
      std::string, 
      std::string, 
      std::string,
      std::vector< IncidentParticle >,
      std::optional< std::string >,
      std::optional< std::string > >(),
    python::arg( "zaid" ), 
    python::arg( "libname" ),
    python::arg( "process" ), 
    python::arg( "incident" ),
    python::arg( "information" ) = std::nullopt,
    python::arg( "source" ) = std::nullopt,
    "Initialise the table\n\n"
    "Arguments:\n"
    "    self               the table\n"
    "    zaid               the zaid of the table\n"
    "    libname            the library name\n"
    "    process            the processing date\n"
    "    incident           a vector of IncidentParticle records\n"
    "    information        the table information line (optional)\n"
    "    source             the source date (optional)\n"
  )
  .def_property_readonly(

    "metadata",
    &Table::metadata,
    "Return the metadata of the table"
  )
  .def_property_readonly(

    "number_incident_particles",
    &Table::numberIncidentParticles,
    "Return the number of incident particles"
  )
  .def(

    "incident_particle",
    &Table::incidentParticle,
    python::arg( "particle" ),
    "Return the record for an incident particle\n\n"
    "Arguments:\n"
    "    self       the table\n"
    "    particle   the incident particle identifier"
  )
  .def_property_readonly(

    "incident_particles",
    &Table::incidentParticles,
    "Return the vector containing all incident particle records"
  );

  // add standard table definitions
  addStandardTableDefinitions< Table >( table );
}
