#ifndef NJOY_NDITK_DEPLETION_PRODUCT
#define NJOY_NDITK_DEPLETION_PRODUCT

// system includes
#include <sstream>
#include <iomanip>

// other includes
#include "tools/std23/views.hpp"
#include "NDItk/base/IntegerListRecord.hpp"
#include "NDItk/depletion/Multiplicities.hpp"

namespace njoy {
namespace NDItk {
namespace depletion {

/**
 *  @brief A reaction identifier and multiplicity subrecord for a given product in depletion data
 */
class Product : protected base::IntegerListRecord {

  /* fields */
  Multiplicities multiplicities_;

public:

  /* constructor */

  #include "NDItk/depletion/Product/src/ctor.hpp"
  #include "NDItk/depletion/Product/src/generateData.hpp"

  /* methods */

  /**
   *  @brief Return the reaction product identifier
   */
  int reactionProduct() const { return this->multiplicities_.identifier(); }

  /**
   *  @brief Return the number of reactions with this product 
   */
  int numberReactions() const { return this->multiplicities_.numberReactionData(); }

  /**
   *  @brief Return the reaction identifiers
   */
  auto reactionIdentifiers() const { return this->multiplicities_.reactionData(); }

  /**
   *  @brief Return the reaction product multiplicities
   */
  auto multiplicities() const { return this->multiplicities_.multiplicities(); }

  using base::IntegerListRecord::keyword;
  using base::IntegerListRecord::values;
  using base::IntegerListRecord::size;
  using base::IntegerListRecord::empty;
  using base::IntegerListRecord::begin;
  using base::IntegerListRecord::end;

  #include "NDItk/depletion/Product/src/read.hpp"
  #include "NDItk/depletion/Product/src/print.hpp"
};

} // depletion namespace
} // NDItk namespace
} // njoy namespace

#endif
