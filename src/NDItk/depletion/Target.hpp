#ifndef NJOY_NDITK_DEPLETION_TARGET
#define NJOY_NDITK_DEPLETION_TARGET

// system includes
#include <sstream>
#include <iomanip>

// other includes
#include "tools/disco/FreeFormatCharacter.hpp"
#include "tools/disco/FreeFormatInteger.hpp"
#include "NDItk/base/Record.hpp"
#include "NDItk/depletion/Product.hpp"

namespace njoy {
namespace NDItk {
namespace depletion {

/**
 *  @brief A target record for depletion data
 */
class Target : protected base::Record {

public:

  /* fields */
  int identifier_;
  std::vector< Product > products_;

  /* constructor */

  #include "NDItk/depletion/Target/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the target particle's identifier
   */
  int targetIdentifier() const { return this->identifier_; }

  /**
   *  @brief Return the number of products for this target
   */
  int numberProducts() const { return this->products_.size(); }

  /**
   *  @brief Return the product data for this target
   */
  const std::vector< Product >& products() const { return this->products_; }

  using base::Record::keyword;

  #include "NDItk/depletion/Target/src/read.hpp"
  #include "NDItk/depletion/Target/src/print.hpp"

};

} // depletion namespace
} // NDItk namespace
} // njoy namespace

#endif
