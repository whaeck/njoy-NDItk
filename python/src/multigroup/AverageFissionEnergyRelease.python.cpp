// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "NDItk/multigroup/AverageFissionEnergyRelease.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"
#include "read.hpp"

// namespace aliases
namespace python = pybind11;

namespace multigroup {

void wrapAverageFissionEnergyRelease( python::module& module, python::module& ) {

  // type aliases
  using Record = njoy::NDItk::multigroup::AverageFissionEnergyRelease;

  // wrap views created by this record

  // create the record
  python::class_< Record > record(

    module,
    "AverageFissionEnergyRelease",
    "An average fission energy release record for multigroup neutron and photon data"
  );

  // wrap the record
  record
  .def(

    python::init< double, double, double,
                  double, double, double >(),
    python::arg( "total" ), python::arg( "prompt" ), python::arg( "neutrons" ),
    python::arg( "gammas" ), python::arg( "betas" ), python::arg( "fragments" ),
    "Initialise the record\n\n"
    "Arguments:\n"
    "    self        the table\n"
    "    total       the total energy release (including delayed particles\n"
    "                and neutrinos)\n"
    "    prompt      the recoverable energy release (total minus delayed\n"
    "                particles and neutrinos)\n"
    "    neutrons    the energy release through prompt neutrons\n"
    "    gammas      the energy release through prompt gammas\n"
    "    betas       the energy release through delayed betas\n"
    "    fragments   the kinetic energy of fission fragments"
  )
  .def_property_readonly(

    "prompt_energy_release",
    &Record::promptEnergyRelease,
    "The prompt energy release (total energy release minus delayed particles\n"
    "and neutrinos)"
  )
  .def_property_readonly(

    "total_energy_release",
    &Record::totalEnergyRelease,
    "The total energy release (including delayed particles and neutrinos)"
  )
  .def_property_readonly(

    "delayed_betas",
    &Record::delayedBetas,
    "The energy release through delayed betas"
  )
  .def_property_readonly(

    "prompt_gammas",
    &Record::promptGammas,
    "The energy release through prompt gammas"
  )
  .def_property_readonly(

    "prompt_neutrons",
    &Record::promptNeutrons,
    "The kinetic energy of the prompt fission neutrons"
  )
  .def_property_readonly(

    "fission_fragments",
    &Record::fissionFragments,
    "The kinetic energy of the fission products"
  )
  .def_static(

    "from_string",
    [] ( const std::string& string ) -> Record
       { return read< Record >( string ); },
    python::arg( "string" ),
    "Read the record from a string\n\n"
    "An exception is raised if something goes wrong while reading the\n"
    "record\n\n"
    "Arguments:\n"
    "    string    the string representing the record"
  );

  // add standard record definitions
  addStandardRecordDefinitions< Record, DoubleRange >( record );
}

} // multigroup namespace
