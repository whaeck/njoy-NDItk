#ifndef NJOY_NDITK_MULTIGROUP_STRUCTURE
#define NJOY_NDITK_MULTIGROUP_STRUCTURE

// system includes

// other includes
#include "tools/Log.hpp"
#include "NDItk/base/RealListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief A group structure record for multigroup neutron and photon data
 */
class Structure : protected base::RealListRecord {

  /* fields */

  /* auxiliary functions */

  #include "NDItk/multigroup/Structure/src/verify.hpp"

public:

  /* constructor */

  #include "NDItk/multigroup/Structure/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of groups defined by this record
   */
  std::size_t numberGroups() const {

    return this->empty() ? 0 : this->size() - 1;
  }

  /**
   *  @brief Return the group structure boundaries
   */
  auto boundaries() const { return this->values(); }

  using base::RealListRecord::keyword;
  using base::RealListRecord::values;
  using base::RealListRecord::size;
  using base::RealListRecord::empty;
  using base::RealListRecord::begin;
  using base::RealListRecord::end;
  using base::RealListRecord::print;

  #include "NDItk/multigroup/Structure/src/read.hpp"
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
