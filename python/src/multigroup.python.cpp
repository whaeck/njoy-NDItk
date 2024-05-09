// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace multigroup {

  // declarations - NDI records and subrecords
  void wrapMetadata( python::module&, python::module& );
  void wrapCrossSection( python::module&, python::module& );
  void wrapFluxWeights( python::module&, python::module& );
  void wrapEnergyGroupStructure( python::module&, python::module& );
  void wrapReactionCrossSections( python::module&, python::module& );
  void wrapTotalCrossSection( python::module&, python::module& );
  void wrapAverageFissionEnergyRelease( python::module&, python::module& );
}

void wrapMultigroup( python::module& module, python::module& viewmodule ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "multigroup",
    "Multigroup neutron and photon NDI records and subrecords"
  );

  multigroup::wrapMetadata( submodule, viewmodule );
  multigroup::wrapCrossSection( submodule, viewmodule );
  multigroup::wrapFluxWeights( submodule, viewmodule );
  multigroup::wrapEnergyGroupStructure( submodule, viewmodule );
  multigroup::wrapReactionCrossSections( submodule, viewmodule );
  multigroup::wrapTotalCrossSection( submodule, viewmodule );
  multigroup::wrapAverageFissionEnergyRelease( submodule, viewmodule );
}
