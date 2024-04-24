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

  FluxWeights() : RealListRecord( "wgts" ) {}

  FluxWeights( std::vector< double > boundaries ) :
      RealListRecord( "wgts", std::move( boundaries ) ) {}

  std::size_t numberGroups() const { return this->size(); }

  using base::RealListRecord::keyword;
  using base::RealListRecord::values;
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
