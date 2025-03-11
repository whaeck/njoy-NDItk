// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "NDItk/depletion/Multiplicities.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace depletion {

void wrapMultiplicities( python::module& module, python::module& ) {

  // type aliases
  using Record = njoy::NDItk::depletion::Multiplicities;

  // wrap views created by this record

  // create the record
  python::class_< Record > record(

    module,
    "Multiplicities",
    "A reaction product multiplicity subrecord for depletion data"
  );

  // wrap the record
  record
  .def(

    python::init< int, std::vector< int >, std::vector< int > >(),
    python::arg( "product" ), python::arg( "reactions" ),
    python::arg( "multiplicities" ),
    "Initialise the subrecord\n\n"
    "Arguments:\n"
    "    self             the record\n"
    "    product          the reaction product identifier\n"
    "    reactions        the reaction identifiers\n"
    "    multiplicities   the multiplicity values"
  )
  .def_property_readonly(

    "reaction_product",
    &Record::reactionProduct,
    "Return the reaction product identifier"
  )
  .def_property_readonly(

    "number_reactions",
    &Record::numberReactions,
    "Return the number of reaction identifiers"
  )
  .def_property_readonly(

    "reaction_identifiers",
    [] ( const Record& self ) -> IntRange
       { return self.reactionIdentifiers(); },
    "Return the reaction product identifiers"
  )
  .def_property_readonly(

    "multiplicities",
    [] ( const Record& self ) -> IntRange
       { return self.multiplicities(); },
    "Return the reaction product multiplicities"
  );

  // add standard record definitions
  addStandardSubrecordDefinitions< Record, IntRange >( record );
}

} // depletion namespace
