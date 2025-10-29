// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace dosimetry {

  // declarations - NDI records and subrecords
  void wrapMetadata( python::module&, python::module& );
}

void wrapDosimetry( python::module& module, python::module& viewmodule ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "dosimetry",
    "Dosimetry NDI records and subrecords"
  );

  dosimetry::wrapMetadata( submodule, viewmodule );
}
