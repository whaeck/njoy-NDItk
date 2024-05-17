#ifndef NJOY_NDITK_MULTIGROUP_LEGENDREMOMENT
#define NJOY_NDITK_MULTIGROUP_LEGENDREMOMENT

// system includes
#include <sstream>
#include <iomanip>

// other includes
#include "tools/std23/views.hpp"
#include "NDItk/base/SubListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief A Legendre moment subrecord for multigroup neutron and photon data
 */
class LegendreMoment : protected base::SubListRecord< LegendreMoment, double > {

  friend class base::SubListRecord< LegendreMoment, double >;
  using Parent = base::SubListRecord< LegendreMoment, double >;

  /* fields */

  std::size_t incident_;
  std::size_t outgoing_;

  /* auxiliary functions */

  #include "NDItk/multigroup/LegendreMoment/src/verify.hpp"
  #include "NDItk/multigroup/LegendreMoment/src/generateData.hpp"
  #include "NDItk/multigroup/LegendreMoment/src/write.hpp"

public:

  /* constructor */

  #include "NDItk/multigroup/LegendreMoment/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the Legendre moment order
   */
  int order() const { return static_cast< int >( std::round( this->value( 0 ) ) ); }

  /**
   *  @brief Return the number of incident groups defined by this record
   */
  int numberPrimaryGroups() const { return this->incident_; }

  /**
   *  @brief Return the number of outgoing groups defined by this record
   */
  int numberOutgoingGroups() const { return this->outgoing_; }

  /**
   *  @brief Return the matrix defined by this record
   */
  auto matrix() const {

    using namespace njoy::tools;
    return this->values( 1, this->size() - 1 )
               | std23::views::chunk( this->numberOutgoingGroups() );
  }

  using Parent::values;
  using Parent::size;
  using Parent::empty;
  using Parent::begin;
  using Parent::end;
  using Parent::print;
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
