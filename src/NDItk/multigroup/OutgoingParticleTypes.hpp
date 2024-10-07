#ifndef NJOY_NDITK_MULTIGROUP_OUTGOINGPARTICLETYPES
#define NJOY_NDITK_MULTIGROUP_OUTGOINGPARTICLETYPES

// system includes

// other includes
#include "tools/Log.hpp"
#include "NDItk/base/IntegerListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief An outgoing particle type record for multigroup neutron data
 */
class OutgoingParticleTypes : protected base::IntegerListRecord {

  /* fields */

  /* auxiliary functions */

  #include "NDItk/multigroup/OutgoingParticleTypes/src/verify.hpp"

public:

  /* constructor */

  #include "NDItk/multigroup/OutgoingParticleTypes/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of outgoing particles defined by this record
   */
  unsigned int numberOutgoingParticles() const { return this->size(); }

  using base::IntegerListRecord::keyword;
  using base::IntegerListRecord::values;
  using base::IntegerListRecord::size;
  using base::IntegerListRecord::empty;
  using base::IntegerListRecord::begin;
  using base::IntegerListRecord::end;
  using base::IntegerListRecord::print;

  #include "NDItk/multigroup/OutgoingParticleTypes/src/read.hpp"
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
