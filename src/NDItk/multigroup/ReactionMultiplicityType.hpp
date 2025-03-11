#ifndef NJOY_NDITK_MULTIGROUP_REACTIONMULTIPLICITYTYPE
#define NJOY_NDITK_MULTIGROUP_REACTIONMULTIPLICITYTYPE

// system includes

// other includes

namespace njoy {
namespace NDItk {
namespace multigroup {

enum class ReactionMultiplicityType : short {

  All = 1,
  Few = 2,
  RMO = 3 //! @todo change this name to be more understandable
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
