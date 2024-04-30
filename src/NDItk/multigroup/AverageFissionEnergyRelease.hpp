#ifndef NJOY_NDITK_MULTIGROUP_FISSIONENERGYRELEASE
#define NJOY_NDITK_MULTIGROUP_FISSIONENERGYRELEASE

// system includes

// other includes
#include "tools/Log.hpp"
#include "NDItk/base/RealListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief An average fission energy release record
 */
class AverageFissionEnergyRelease : protected base::RealListRecord {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */

  #include "NDItk/multigroup/AverageFissionEnergyRelease/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of groups defined by this record
   */
  std::size_t numberGroups() const {

    return this->empty() ? 0 : this->size() - 1;
  }

  using base::RealListRecord::keyword;
  using base::RealListRecord::values;
  using base::RealListRecord::size;
  using base::RealListRecord::empty;
  using base::RealListRecord::begin;
  using base::RealListRecord::end;
  using base::RealListRecord::print;

  #include "NDItk/multigroup/AverageFissionEnergyRelease/src/read.hpp"
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
