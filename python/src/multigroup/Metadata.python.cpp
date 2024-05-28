// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "NDItk/multigroup/Metadata.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"
#include "read.hpp"

// namespace aliases
namespace python = pybind11;

namespace multigroup {

void wrapMetadata( python::module& module, python::module& ) {

  // type aliases
  using Record = njoy::NDItk::multigroup::Metadata;

  // wrap views created by this record

  // create the record
  python::class_< Record > record(

    module,
    "Metadata",
    "A group Metadata record for multigroup neutron and photon data"
  );

  // wrap the record
  record
  .def(

    python::init< std::string, std::string, std::string,
                  double, double, double,
                  unsigned int, std::map< unsigned int, unsigned int >,
                  unsigned int,
                  std::optional< std::string >,
                  std::optional< double >,
                  std::optional< unsigned int >,
                  std::optional< unsigned int > >(),
    python::arg( "zaid" ), python::arg( "libname" ),
    python::arg( "process" ), python::arg( "awr" ),
    python::arg( "temperature" ), python::arg( "dilution" ), python::arg( "groups" ),
    python::arg( "outgoing" ), python::arg( "reactions" ),
    python::arg( "source" ) = std::nullopt,
    python::arg( "weight" ) = std::nullopt,
    python::arg( "upscatter" ) = std::nullopt,
    python::arg( "downscatter" ) = std::nullopt,
    "Initialise the record\n\n"
    "Arguments:\n"
    "    self           the metadata\n"
    "    zaid           the zaid of the table\n"
    "    libname        the library name\n"
    "    process        the processing date\n"
    "    awr            the atomic weight ratio of the target (with respect\n"
    "                   to the neutron mass)\n"
    "    temperature    the temperature of the target\n"
    "    dilution       the dilution (aka sigma0)\n"
    "    groups         the number of groups in the primary group structure\n"
    "    outgoing       the number of groups in the outgoing group structures\n"
    "    reactions      the number of reactions defined in the table\n"
    "    source         the source date (optional)\n"
    "    weight         the atomic weight of the target (optional)\n"
    "    upscatter      the number of upscatter groups (optional)\n"
    "    downscatter    the number of downscatter groups (optional)"
  )
  .def_property_readonly(

    "zaid",
    &Record::zaid,
    "The zaid of the table"
  )
  .def_property_readonly(

    "library_name",
    &Record::libraryName,
    "The library name"
  )
  .def_property_readonly(

    "source_date",
    &Record::sourceDate,
    "The source date"
  )
  .def_property_readonly(

    "process_date",
    &Record::processDate,
    "The process date"
  )
  .def_property_readonly(

    "atomic_weight_ratio",
    &Record::atomicWeightRatio,
    "The atomic weight ratio of the target (with respect to the neutron mass)"
  )
  .def_property_readonly(

    "atomic_weight",
    &Record::atomicWeight,
    "The atomic weight of the target"
  )
  .def_property_readonly(

    "temperature",
    &Record::temperature,
    "The temperature of the target"
  )
  .def_property_readonly(

    "dilution",
    &Record::dilution,
    "The dilution (aka sigma0)"
  )
  .def_property_readonly(

    "number_groups",
    &Record::numberGroups,
    "The number of groups defined by this record"
  )
  .def_property_readonly(

    "number_upscatter_groups",
    &Record::numberUpscatterGroups,
    "The number of upscatter groups defined by this record"
  )
  .def_property_readonly(

    "number_downscatter_groups",
    &Record::numberDownscatterGroups,
    "The number of downscatter groups defined by this record"
  )
  .def(

    "number_outgoing_groups",
    &Record::numberOutgoingGroups,
    python::arg( "particle" ),
    "The number of outgoing groups defined by this record for the particle\n\n"
    "Arguments:\n"
    "    self       the metadata\n"
    "    particle   the outgoing particle identifier"
  )
  .def_property_readonly(

    "number_reactions",
    &Record::numberReactions,
    "The number of reactions defined by this record"
  )
  .def(

    "to_string",
    [] ( const Record& self ) -> std::string {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      self.print( output );
      return buffer;
    },
    "Return the string representation of the subrecord\n\n"
    "Arguments:\n"
    "    self    the metadata"
  );
}

} // multigroup namespace
