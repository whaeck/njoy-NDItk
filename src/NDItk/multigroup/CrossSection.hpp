#ifndef NJOY_NDITK_MULTIGROUP_CROSSSECTION
#define NJOY_NDITK_MULTIGROUP_CROSSSECTION

// system includes
#include <sstream>
#include <iomanip>

// other includes
#include "NDItk/base/SubListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief A cross section subrecord
 */
class CrossSection : protected base::SubListRecord< CrossSection, double > {

  friend class base::SubListRecord< CrossSection, double >;
  using Parent = base::SubListRecord< CrossSection, double >;

  /* auxiliary functions */

  #include "NDItk/multigroup/CrossSection/src/generateData.hpp"
  #include "NDItk/multigroup/CrossSection/src/write.hpp"

public:

  /* constructor */

  #include "NDItk/multigroup/CrossSection/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the reaction identifier
   */
  int identifier() const { return static_cast< int >( std::round( this->value( 0 ) ) ); }

  /**
   *  @brief Return the reaction Q value
   */
  double qvalue() const { return this->value( 1 ); }

  /**
   *  @brief Return the cross section values
   */
  auto crossSections() const { return this->values( 2, this->numberGroups() ); }

  /**
   *  @brief Return the number of groups defined by this record
   */
  std::size_t numberGroups() const { return this->length() - 2; }

  using Parent::begin;
  using Parent::end;
  using Parent::empty;
  using Parent::print;
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
