// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "NDItk/MultigroupTable.hpp"
#include "definitions.hpp"
#include "read.hpp"

// namespace aliases
namespace python = pybind11;

void wrapMultigroupTable( python::module& module, python::module& ) {

  // type aliases
  using Table = njoy::NDItk::MultigroupTable;
  using Metadata = njoy::NDItk::multigroup::Metadata;
  using Structure = njoy::NDItk::multigroup::Structure;
  using FluxWeights = njoy::NDItk::multigroup::FluxWeights;
  using ReactionCrossSections = njoy::NDItk::multigroup::ReactionCrossSections;
  using AverageFissionEnergyRelease = njoy::NDItk::multigroup::AverageFissionEnergyRelease;

  // wrap views created by this table

  // create the table
  python::class_< Table > table(

    module,
    "MultigroupTable",
    "A multigroup neutron and photon table"
  );

  // wrap the table
  table
  .def(

    python::init< std::string, std::string, std::string, std::string,
                  double, double, double, double,
                  Structure, FluxWeights,
                  ReactionCrossSections,
                  std::optional< AverageFissionEnergyRelease > >(),
    python::arg( "zaid" ), python::arg( "libname" ), python::arg( "source" ),
    python::arg( "process" ), python::arg( "awr" ), python::arg( "weight" ),
    python::arg( "temperature" ), python::arg( "dilution" ),
    python::arg( "structure" ), python::arg( "flux" ), python::arg( "xs" ),
    python::arg( "release" ) = std::nullopt,
    "Initialise the table\n\n"
    "Arguments:\n"
    "    self           the table\n"
    "    zaid           the zaid of the table\n"
    "    libname        the library name\n"
    "    source         the source date\n"
    "    process        the processing date\n"
    "    awr            the atomic weight ratio of the target (with respect\n"
    "                   to the neutron mass)\n"
    "    weight         the atomic weight of the target\n"
    "    temperature    the temperature of the target\n"
    "    dilution       the dilution (aka sigma0)\n"
    "    structure      the primary group structure\n"
    "    flux           the flux weights\n"
    "    xs             the reaction cross section data\n"
    "    release        the average fission energy release data"
  )
  .def_property_readonly(

    "metadata",
    &Table::metadata,
    "The metadata of the table"
  )
  .def_property_readonly(

    "structure",
    &Table::structure,
    "The primary group structure record"
  )
  .def_property_readonly(

    "flux",
    &Table::flux,
    "The flux weight record"
  )
  .def_property_readonly(

    "reaction_cross_sections",
    &Table::reactionCrossSections,
    "The reaction cross section record"
  )
  .def_property_readonly(

    "average_fission_energy_release",
    &Table::averageFissionEnergyRelease,
    "The average fission energy release record"
  );

  // add standard table definitions
  addStandardTableDefinitions< Table >( table );
}
