#ifndef NJOY_NDITK_DEPLETION_PRODUCT
#define NJOY_NDITK_DEPLETION_PRODUCT

// system includes
#include <sstream>
#include <iomanip>

// other includes
#include "tools/std23/views.hpp"
#include "NDItk/base/SubListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace depletion {

/**
 *  @brief A reaction identifier and multiplicity subrecord for a given product in depletion data
 */
class Product : protected base::SubListRecord< Product, int > {

  friend class base::SubListRecord< Product, int >;
  using Parent = base::SubListRecord< Product, int >;

  /* auxiliary functions */

  #include "NDItk/depletion/Product/src/verify.hpp"
  #include "NDItk/depletion/Product/src/generateData.hpp"
  #include "NDItk/depletion/Product/src/write.hpp"

public:

  /* constructor */

  #include "NDItk/depletion/Product/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the reaction product identifier
   */
  int reactionProduct() const { return this->value( 0 ); }

  /**
   *  @brief Return the number of reactions with this product 
   */
  int numberReactions() const { return this->value( 1 ); }

  /**
   *  @brief Return the reaction identifiers
   */
  auto reactionIdentifiers() const {

    using namespace njoy::tools;
    return this->values( 2, 2 * this->numberReactions() )
               | std23::views::stride( 2 );
  }

  /**
   *  @brief Return the reaction product multiplicities
   */
  auto multiplicities() const {

    using namespace njoy::tools;
    return this->values( 3, 2 * this->numberReactions() )
               | std23::views::stride( 2 );
  }

  using Parent::values;
  using Parent::size;
  using Parent::empty;
  using Parent::begin;
  using Parent::end;
  using Parent::print;
};

} // depletion namespace
} // NDItk namespace
} // njoy namespace

#endif
