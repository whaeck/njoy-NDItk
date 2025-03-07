// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "NDItk/depletion/Multiplicities.hpp"
#include "NDItk/depletion/Product.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace depletion {

void wrapProduct( python::module& module, python::module& ) {

  // type aliases
  using Record = njoy::NDItk::depletion::Product;
  using Multiplicities = njoy::NDItk::depletion::Multiplicities;

  // wrap views created by this record

  // create the record
  python::class_< Record > record(

    module,
    "Product",
    "A product record for depletion data"
  );

  // wrap the record
  record
  .def(

    python::init< Multiplicities >(),
    python::arg( "multiplicities" ),
    "Initialise the subrecord\n\n"
    "Arguments:\n"
    "    self              the record\n"
    "    multiplicities    a depletion::Multiplicities SubListRecord"
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
    "Return the reaction multiplicities"
  );

  // add standard record definitions
  addStandardRecordDefinitions<Record, IntRange >( record );
}

} // depletion namespace
