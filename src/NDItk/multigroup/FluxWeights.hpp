#ifndef NJOY_NDITK_MULTIGROUP_FLUXWEIGHTS
#define NJOY_NDITK_MULTIGROUP_FLUXWEIGHTS

// system includes

// other includes
#include "NDItk/base/RealListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief A flux weight record
 */
class FluxWeights : protected base::RealListRecord {

  /* fields */

public:

  /* constructor */

  #include "NDItk/multigroup/FluxWeights/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of groups defined by this record
   */
  std::size_t numberGroups() const { return this->size(); }

  /**
   *  @brief Return the flux weights
   */
  auto weights() const { return this->values(); }

  using base::RealListRecord::keyword;
  using base::RealListRecord::size;
  using base::RealListRecord::empty;
  using base::RealListRecord::begin;
  using base::RealListRecord::end;
  using base::RealListRecord::read;
  using base::RealListRecord::print;
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
