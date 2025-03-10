// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "NDItk/depletion/Target.hpp"
#include "NDItk/depletion/Product.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"
#include "read.hpp"

// namespace aliases
namespace python = pybind11;

namespace depletion {

void wrapTarget( python::module& module, python::module& ) {

  // type aliases
  using Record  = njoy::NDItk::depletion::Target;
  using Product = njoy::NDItk::depletion::Product;

  // wrap views created by this record

  // create the record
  python::class_< Record > record(

    module,
    "Target",
    "A target record for depletion data"
  );

  // wrap the record
  record
  .def(

    python::init< int, std::vector< Product > >(),
    python::arg( "identifier" ),
    python::arg( "products" ),
    "Initialise the record\n\n"
    "Arguments:\n"
    "    self              the record\n"
    "    identifier        the target particle identifier"
    "    products          a vector of depletion products"
  )
  .def_property_readonly(

    "target_identifier",
    &Record::targetIdentifier,
    "Return the target particle identifier"
  )
  .def_property_readonly(

    "number_products",
    &Record::numberProducts,
    "Return the number of products for this target"
  )
  .def_property_readonly(

    "products",
    &Record::products,
    "Return the product data for this target"
  )
/*
  .def_property_readonly(

    "keyword",
    &Record::keyword,
    "The record keyword"
  )
*/
  ;

  // add standard record definitions
  addBaseRecordDefinitions<Record>( record );
}

} // depletion namespace
