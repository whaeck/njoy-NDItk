// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "NDItk/multigroup/ReactionCrossSections.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"
#include "read.hpp"

// namespace aliases
namespace python = pybind11;

namespace multigroup {

void wrapReactionCrossSections( python::module& module, python::module& ) {

  // type aliases
  using Record = njoy::NDItk::multigroup::ReactionCrossSections;
  using CrossSection = njoy::NDItk::multigroup::CrossSection;

  // wrap views created by this record

  // create the record
  python::class_< Record > record(

    module,
    "ReactionCrossSections",
    "A reaction cross section record for multigroup neutron and photon data"
  );

  // wrap the record
  record
  .def(

    python::init< std::vector< CrossSection > >(),
    python::arg( "xs" ),
    "Initialise the record\n\n"
    "Arguments:\n"
    "    self   the record\n"
    "    xs     the cross section data"
  )
  .def_property_readonly(

    "number_groups",
    &Record::numberGroups,
    "The number of groups defined by this record"
  )
  .def_property_readonly(

    "number_reactions",
    &Record::numberReactions,
    "The number of reactions defined by this record"
  )
  .def_property_readonly(

    "reactions",
    &Record::reactions,
    "The cross section data for all reactions"
  )
  .def(

    "has_reaction",
    &Record::hasReaction,
    python::arg( "reaction" ),
    "Return whether or not a given reaction is present\n\n"
    "    self        the record\n"
    "    reaction    the reaction to look for"
  )
  .def(

    "reaction",
    &Record::reaction,
    python::arg( "reaction" ),
    "Return the cross section data for a given reaction\n\n"
    "    self        the record\n"
    "    reaction    the reaction to look for"
  )
  .def_static(

    "from_string",
    [] ( const std::string& string, std::size_t reactions, 
         std::size_t groups ) -> Record
       { return read< Record >( string, reactions, groups ); },
    python::arg( "string" ), python::arg( "reactions" ),
    python::arg( "groups" ),
    "Read the record from a string\n\n"
    "An exception is raised if something goes wrong while reading the\n"
    "record\n\n"
    "Arguments:\n"
    "    string      the string representing the record\n"
    "    reactions   the number of reactions to be read\n"
    "    groups      the number of groups to be read"
  );

  // add standard record definitions
  addStandardRecordDefinitions< Record, DoubleRange >( record );
}

} // multigroup namespace
