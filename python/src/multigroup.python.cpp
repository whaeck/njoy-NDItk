// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace multigroup {

  // declarations - NDI records and subrecords
  void wrapCrossSection( python::module&, python::module& );
}

void wrapMultigroup( python::module& module, python::module& viewmodule ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "multigroup",
    "Multigroup neutron and photon NDI records and subrecords"
  );

  multigroup::wrapCrossSection( submodule, viewmodule );
}
