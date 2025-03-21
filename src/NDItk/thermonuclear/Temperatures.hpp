#ifndef NJOY_NDITK_THERMONUCLEAR_TEMPERATURES
#define NJOY_NDITK_THERMONUCLEAR_TEMPERATURES

// system includes

// other includes
#include "tools/Log.hpp"
#include "NDItk/base/RealListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace thermonuclear {

/**
 *  @brief A temperature record for thermonuclear data
 */
class Temperatures : protected base::RealListRecord {

  /* fields */

  /* auxiliary functions */

  #include "NDItk/thermonuclear/Temperatures/src/verify.hpp"

public:

  /* constructor */

  #include "NDItk/thermonuclear/Temperatures/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of temperatures defined by this record
   */
  unsigned int numberTemperatures() const { return this->size(); }

  using base::RealListRecord::keyword;
  using base::RealListRecord::particle;
  using base::RealListRecord::values;
  using base::RealListRecord::size;
  using base::RealListRecord::empty;
  using base::RealListRecord::begin;
  using base::RealListRecord::end;
  using base::RealListRecord::print;

  #include "NDItk/thermonuclear/Temperatures/src/read.hpp"
};

} // thermonuclear namespace
} // NDItk namespace
} // njoy namespace

#endif
