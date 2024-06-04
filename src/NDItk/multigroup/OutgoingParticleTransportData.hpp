#ifndef NJOY_NDITK_MULTIGROUP_OUTGOINGPARTICLETRANSPORTDATA
#define NJOY_NDITK_MULTIGROUP_OUTGOINGPARTICLETRANSPORTDATA

// system includes

// other includes
#include "tools/Log.hpp"
#include "NDItk/base/StringListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief An outgoing particle type record for multigroup neutron and photon data
 */
class OutgoingParticleTransportData : protected base::StringListRecord {

  /* fields */

  /* auxiliary functions */

  #include "NDItk/multigroup/OutgoingParticleTransportData/src/verify.hpp"

public:

  /* constructor */

  #include "NDItk/multigroup/OutgoingParticleTransportData/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of outgoing particles defined by this record
   */
  unsigned int numberOutgoingParticles() const { return this->size(); }

  using base::StringListRecord::keyword;
  using base::StringListRecord::values;
  using base::StringListRecord::size;
  using base::StringListRecord::empty;
  using base::StringListRecord::begin;
  using base::StringListRecord::end;
  using base::StringListRecord::print;

  #include "NDItk/multigroup/OutgoingParticleTransportData/src/read.hpp"
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
