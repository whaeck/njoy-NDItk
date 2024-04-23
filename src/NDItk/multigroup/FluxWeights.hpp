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

  using base::RealListRecord::keyword;

  decltype(auto) weights() const { return this->content(); }

  std::size_t numberGroups() const {

    if ( this->hasContent() ) {

      return this->weights().value().size();
    }
    else {

      return 0;
    }
  }

  using base::RealListRecord::hasContent;

  using base::RealListRecord::read;
  using base::RealListRecord::print;
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
