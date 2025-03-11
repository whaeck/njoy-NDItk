// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "NDItk/multigroup/ReactionMultiplicityType.hpp"

// namespace aliases
namespace python = pybind11;

namespace multigroup {

void wrapReactionMultiplicityType( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::NDItk::multigroup::ReactionMultiplicityType;

  // wrap views created by this component

  // create the component
  python::enum_< Component > component(

    module,
    "ReactionMultiplicityType",
    "The reaction multiplicity types",
    python::arithmetic()
  );

  // wrap the component
  component
  .value( "All", Component::All )
  .value( "Few", Component::Few )
  .value( "RMO", Component::RMO );
}

} // namespace multigroup
