#ifndef NJOY_NDITK_DEPLETION_INCIDENTPARTICLE
#define NJOY_NDITK_DEPLETION_INCIDENTPARTICLE

// system includes
#include <sstream>
#include <iomanip>

// other includes
#include "tools/disco/FreeFormatCharacter.hpp"
#include "tools/disco/FreeFormatInteger.hpp"
#include "NDItk/base/Record.hpp"
#include "NDItk/depletion/Target.hpp"

namespace njoy {
namespace NDItk {
namespace depletion {

/**
 *  @brief An incident particle record for depletion data
 */
class IncidentParticle : protected base::Record {

  /* auxiliary functions */

  #include "NDItk/depletion/IncidentParticle/src/verify.hpp"

public:

  /* fields */
  int identifier_;
  std::vector< Target > targets_;

  /* constructor */

  #include "NDItk/depletion/IncidentParticle/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the incident particle identifier
   */
  int incidentIdentifier() const { return this->identifier_; }

  /**
   *  @brief Return the number of targets for this incident particle
   */
  int numberTargets() const { return this->targets_.size(); }

  /**
   *  @brief Return the target data for this incident particle
   */
  const std::vector< Target >& targets() const { return this->targets_; }

  using base::Record::keyword;

  #include "NDItk/depletion/IncidentParticle/src/read.hpp"
  #include "NDItk/depletion/IncidentParticle/src/print.hpp"

};

} // depletion namespace
} // NDItk namespace
} // njoy namespace

#endif
