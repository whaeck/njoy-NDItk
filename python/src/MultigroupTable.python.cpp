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
  using EnergyGroupStructure = njoy::NDItk::multigroup::EnergyGroupStructure;
  using FluxWeights = njoy::NDItk::multigroup::FluxWeights;
  using TotalCrossSection = njoy::NDItk::multigroup::TotalCrossSection;
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

    python::init< std::string, std::string, std::string,
                  double, double, double,
                  EnergyGroupStructure,
                  std::vector< EnergyGroupStructure >,
                  FluxWeights,
                  TotalCrossSection,
                  ReactionCrossSections,
                  std::optional< std::string >,
                  std::optional< double >,
                  std::optional< AverageFissionEnergyRelease > >(),
    python::arg( "zaid" ), python::arg( "libname" ),
    python::arg( "process" ), python::arg( "awr" ),
    python::arg( "temperature" ), python::arg( "dilution" ),
    python::arg( "structure" ), python::arg( "outgoing" ),
    python::arg( "flux" ), python::arg( "total" ), python::arg( "xs" ),
    python::arg( "source" ) = std::nullopt,
    python::arg( "weight" ) = std::nullopt,
    python::arg( "release" ) = std::nullopt,
    "Initialise the table\n\n"
    "Arguments:\n"
    "    self           the table\n"
    "    zaid           the zaid of the table\n"
    "    libname        the library name\n"
    "    process        the processing date\n"
    "    awr            the atomic weight ratio of the target (with respect\n"
    "                   to the neutron mass)\n"
    "    temperature    the temperature of the target\n"
    "    dilution       the dilution (aka sigma0)\n"
    "    structure      the primary group structure\n"
    "    outgoing       the outgoing particle group structures\n"
    "    flux           the flux weights\n"
    "    total          the total cross section\n"
    "    xs             the reaction cross section data\n"
    "    source         the source date (optional)\n"
    "    weight         the atomic weight of the target (optional)\n"
    "    release        the average fission energy release data (optional)"
  )
  .def_property_readonly(

    "metadata",
    &Table::metadata,
    "The metadata of the table"
  )
  .def_property_readonly(

    "primary_group_boundaries",
    &Table::primaryGroupBoundaries,
    "The primary group structure record"
  )
  .def(

    "outgoing_group_boundaries",
    &Table::outgoingGroupBoundaries,
    python::arg( "particle" ),
    "The group structure record for an outgoing particle\n\n"
    "Arguments:\n"
    "    self       the metadata\n"
    "    particle   the outgoing particle identifier"
  )
  .def_property_readonly(

    "flux_weights",
    &Table::fluxWeights,
    "The flux weight record"
  )
  .def_property_readonly(

    "reaction_cross_sections",
    &Table::reactionCrossSections,
    "The reaction cross section record"
  )
  .def_property_readonly(

    "total_cross_section",
    &Table::totalCrossSection,
    "The total cross section record"
  )
  .def_property_readonly(

    "average_fission_energy_release",
    &Table::averageFissionEnergyRelease,
    "The average fission energy release record"
  );

  // add standard table definitions
  addStandardTableDefinitions< Table >( table );
}
