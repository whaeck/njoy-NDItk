// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "NDItk/depletion/Product.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace depletion {

void wrapProduct( python::module& module, python::module& ) {

  // type aliases
  using Record = njoy::NDItk::depletion::Product;

  // wrap views created by this record

  // create the record
  python::class_< Record > record(

    module,
    "Product",
    "A reaction identifier and multiplicity subrecord for a given product in depletion data"
  );

  // wrap the record
  record
  .def(

    python::init< int, std::vector< int >, std::vector< int > >(),
    python::arg( "product" ), python::arg( "reactions" ),
    python::arg( "multiplicities" ),
    "Initialise the subrecord\n\n"
    "Arguments:\n"
    "    self              the record\n"
    "    product           the reaction product identifier\n"
    "    reactions         the reaction identifier values\n"
    "    multiplicities    the multiplicity values"
  )
  .def_property_readonly(

    "reaction_product",
    &Record::reactionProduct,
    "Return the reaction product identifier"
  )
  .def_property_readonly(

    "number_reactions",
    &Record::numberReactions,
    "Return the number of reactions with this product"
  )
  .def_property_readonly(

    "reaction_identifiers",
    [] ( const Record& self ) -> IntRange
       { return self.reactionIdentifiers(); },
    "Return the reaction identifiers"
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
