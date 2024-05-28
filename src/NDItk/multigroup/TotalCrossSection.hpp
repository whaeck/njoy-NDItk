#ifndef NJOY_NDITK_MULTIGROUP_TOTALCROSSSECTION
#define NJOY_NDITK_MULTIGROUP_TOTALCROSSSECTION

// system includes

// other includes
#include "tools/Log.hpp"
#include "NDItk/base/RealListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief A total cross section record for multigroup neutron and photon data
 */
class TotalCrossSection : protected base::RealListRecord {

  /* fields */

  /* auxiliary functions */

  #include "NDItk/multigroup/TotalCrossSection/src/verify.hpp"

public:

  /* constructor */

  #include "NDItk/multigroup/TotalCrossSection/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of groups defined by this record
   */
  std::size_t numberGroups() const { return this->size(); }

  using base::RealListRecord::keyword;
  using base::RealListRecord::values;
  using base::RealListRecord::size;
  using base::RealListRecord::empty;
  using base::RealListRecord::begin;
  using base::RealListRecord::end;
  using base::RealListRecord::print;

  #include "NDItk/multigroup/TotalCrossSection/src/read.hpp"
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
