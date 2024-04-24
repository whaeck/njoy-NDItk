#ifndef NJOY_NDITK_MULTIGROUP_STRUCTURE
#define NJOY_NDITK_MULTIGROUP_STRUCTURE

// system includes

// other includes
#include "NDItk/base/RealListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief A group structure record
 */
class Structure : protected base::RealListRecord {

  /* fields */

public:

  Structure() : RealListRecord( "e_bounds" ) {}
  Structure( unsigned int particle ) :
      RealListRecord( std::string( "e_bounds_" ) + std::to_string( particle ) ) {}

  Structure( std::vector< double > boundaries ) :
      RealListRecord( "e_bounds", std::move( boundaries ) ) {}
  Structure( unsigned int particle, std::vector< double > boundaries ) :
      RealListRecord( std::string( "e_bounds_" ) + std::to_string( particle ),
                      std::move( boundaries ) ) {}

  using base::RealListRecord::keyword;

  std::size_t numberGroups() const {

    if ( ! this->empty() ) {

      return this->size() - 1;
    }
    else {

      return 0;
    }
  }

  using base::RealListRecord::values;
  using base::RealListRecord::size;
  using base::RealListRecord::empty;

  using base::RealListRecord::read;
  using base::RealListRecord::print;
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
