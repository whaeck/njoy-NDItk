// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "NDItk/thermonuclear/InterpolationRegions.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace thermonuclear {

void wrapInterpolationRegions( python::module& module, python::module& ) {

  // type aliases
  using Record = njoy::NDItk::thermonuclear::InterpolationRegions;

  // wrap views created by this record

  // create the record
  python::class_< Record > record(

    module,
    "InterpolationRegions",
    "A subrecord for representing interpolate data regions"
  );

  // wrap the record
  record
  .def(

    python::init< std::vector< int >, 
                  std::vector< int> >(),
    python::arg( "endIndices" ),
    python::arg( "interpTypes" ),
    "Initialise the subrecord\n\n"
    "Arguments:\n"
    "    self           the subrecord\n"
    "    endIndices     1-based indices signifying the inclusive end of each region's data"
    "    interpTypes    integers specifying the interpolation type for each region"
  )
  .def_property_readonly(

    "number_interpolation_regions",
    &Record::numberInterpolationRegions,
    "Return the number of interpolation regions"
  )
  .def_property_readonly(

    "boundaries",
    [] ( const Record& self ) -> IntRange
       { return self.boundaries(); },
    "Return the 1-based indices for the end of each region"
  )
  .def_property_readonly(

    "interpolants",
    [] ( const Record& self ) -> IntRange
       { return self.interpolants(); },
    "Return the interpolation types"
  );

  // add standard record definitions
  addStandardSubrecordDefinitions< Record, IntRange >( record );
}

} // thermonuclear namespace
