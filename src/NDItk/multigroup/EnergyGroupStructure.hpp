#ifndef NJOY_NDITK_MULTIGROUP_ENERGYGROUPSTRUCTURE
#define NJOY_NDITK_MULTIGROUP_ENERGYGROUPSTRUCTURE

// system includes

// other includes
#include "tools/Log.hpp"
#include "NDItk/base/RealListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief An energy group structure record for multigroup neutron and photon data
 *
 *  This corresponds to an e_bounds or e_bounds_x record for the primary
 *  energy boundaries or outgoing particle energy boundaries.
 *
 *  The boundary values are given in MeV and must in be descending order.
 *  The number of values is equal to the number of groups plus 1 (the
 *  corresponding num_grps or num_grps_x metadata records must be given
 *  before the energy group structure record can be read).
 */
class EnergyGroupStructure : protected base::RealListRecord {

  /* fields */

  /* auxiliary functions */

  #include "NDItk/multigroup/EnergyGroupStructure/src/verify.hpp"

public:

  /* constructor */

  #include "NDItk/multigroup/EnergyGroupStructure/src/ctor.hpp"

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

  #include "NDItk/multigroup/EnergyGroupStructure/src/read.hpp"
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
