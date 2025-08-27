// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace thermonuclear {

  // declarations - NDI records and subrecords
  void wrapTemperatures( python::module&, python::module& );
  void wrapInterpolationRegions( python::module&, python::module& );
}

void wrapThermonuclear( python::module& module, python::module& viewmodule ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "thermonuclear",
    "thermonuclear NDI records and subrecords"
  );

  thermonuclear::wrapTemperatures( submodule, viewmodule );
  thermonuclear::wrapInterpolationRegions( submodule, viewmodule );
}
