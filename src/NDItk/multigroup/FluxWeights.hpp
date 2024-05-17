#ifndef NJOY_NDITK_MULTIGROUP_FLUXWEIGHTS
#define NJOY_NDITK_MULTIGROUP_FLUXWEIGHTS

// system includes

// other includes
#include "tools/Log.hpp"
#include "NDItk/base/RealListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief A flux weight record for multigroup neutron and photon data
 */
class FluxWeights : protected base::RealListRecord {

  /* fields */

  /* auxiliary functions */

  #include "NDItk/multigroup/FluxWeights/src/verify.hpp"

public:

  /* constructor */

  #include "NDItk/multigroup/FluxWeights/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of groups defined by this record
   */
  unsigned int numberGroups() const { return this->size(); }

  using base::RealListRecord::keyword;
  using base::RealListRecord::values;
  using base::RealListRecord::size;
  using base::RealListRecord::empty;
  using base::RealListRecord::begin;
  using base::RealListRecord::end;
  using base::RealListRecord::print;

  #include "NDItk/multigroup/FluxWeights/src/read.hpp"
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
