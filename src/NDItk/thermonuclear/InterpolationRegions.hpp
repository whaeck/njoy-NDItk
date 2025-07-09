#ifndef NJOY_NDITK_THERMONUCLEAR_INTERPOLATIONREGIONS 
#define NJOY_NDITK_THERMONUCLEAR_INTERPOLATIONREGIONS 

// system includes
#include <sstream>
#include <iomanip>

// other includes
#include "NDItk/base/ColumnData.hpp"

namespace njoy {
namespace NDItk {
namespace thermonuclear {

/**
 *  @brief 
 */
class InterpolationRegions : protected base::ColumnData<int, 2> {

  friend class base::ColumnData<int, 2>;
  using Parent = base::ColumnData<int, 2>;

  /* auxiliary functions */

  #include "NDItk/thermonuclear/InterpolationRegions/src/verify.hpp"
  #include "NDItk/thermonuclear/InterpolationRegions/src/generateData.hpp"

public:

  /* constructor */

  #include "NDItk/thermonuclear/InterpolationRegions/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of interpolation regions
   */
  auto numberInterpolationRegions() const { return this->numberRows(); }

  /**
   *  @brief Return the 1-based indices for the end of each region
   */
  auto boundaries() const { return this->getColumn(0); };

  /**
   *  @brief Return the interpolation types
   */
  auto interpolants() const { return this->getColumn(1); };

  using Parent::values;
  using Parent::size;
  using Parent::empty;
  using Parent::begin;
  using Parent::end;

  #include "NDItk/thermonuclear/InterpolationRegions/src/print.hpp"
};

} // thermonuclear namespace
} // NDItk namespace
} // njoy namespace

#endif
