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
