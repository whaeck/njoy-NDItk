#ifndef NJOY_NDITK_MULTIGROUP_AVERAGEFISSIONENERGYRELEASE
#define NJOY_NDITK_MULTIGROUP_AVERAGEFISSIONENERGYRELEASE

// system includes

// other includes
#include "tools/Log.hpp"
#include "NDItk/base/RealListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief An average fission energy release record for multigroup
 *         neutron data
 */
class AverageFissionEnergyRelease : protected base::RealListRecord {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */

  #include "NDItk/multigroup/AverageFissionEnergyRelease/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the prompt energy release (total energy release
   *         minus delayed particles and neutrinos)
   */
  double promptEnergyRelease() const {

    return this->values()[0];
  }

  /**
   *  @brief Return the total energy release (including delayed particles
   *         and neutrinos)
   */
  double totalEnergyRelease() const {

    return this->values()[1];
  }

  /**
   *  @brief Return the energy release through delayed betas
   */
  double delayedBetas() const {

    return this->values()[2];
  }

  /**
   *  @brief Return the energy release through prompt gammas
   */
  double promptGammas() const {

    return this->values()[3];
  }

  /**
   *  @brief Return the kinetic energy of the prompt fission neutrons
   */
  double promptNeutrons() const {

    return this->values()[5];
  }

  /**
   *  @brief Return the kinetic energy of the fission products
   */
  double fissionFragments() const {

    return this->values()[4];
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
