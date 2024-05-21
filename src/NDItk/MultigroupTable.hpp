#ifndef NJOY_NDITK_MULTIGROUP
#define NJOY_NDITK_MULTIGROUP

// system includes

// other includes
#include "tools/Log.hpp"
#include "NDItk/multigroup/Metadata.hpp"
#include "NDItk/multigroup/Structure.hpp"
#include "NDItk/multigroup/FluxWeights.hpp"
#include "NDItk/multigroup/ReactionCrossSections.hpp"

namespace njoy {
namespace NDItk {

/**
 *  @brief A multigroup NDI table
 */
class MultigroupTable {

  /* fields */

  multigroup::Metadata metadata_;
  multigroup::Structure structure_;
  multigroup::FluxWeights weights_;
  multigroup::ReactionCrossSections xs_;

  /* auxiliary functions */

  #include "NDItk/MultigroupTable/src/readRecord.hpp"
  #include "NDItk/MultigroupTable/src/verify.hpp"

public:

  /* constructor */

  #include "NDItk/MultigroupTable/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the metadata of the table
   */
  const multigroup::Metadata& metadata() const { return this->metadata_; }

  /**
   *  @brief Return the primary group structure record
   */
  const multigroup::Structure& structure() const { return this->structure_; }

  /**
   *  @brief Return the flux weight record
   */
  const multigroup::FluxWeights& flux() const { return this->weights_; }

  /**
   *  @brief Return the reaction cross section record
   */
  const multigroup::ReactionCrossSections& reactionCrossSections() const {

    return this->xs_;
  }

  #include "NDItk/MultigroupTable/src/read.hpp"

  /**
   *  @brief Print the NDI table
   *
   *  @param[in] iter   the current position in the output
   */
  template< typename OutputIterator >
  void print( OutputIterator& iter ) const {

    this->metadata_.print( iter );
    this->structure_.print( iter );
    this->weights_.print( iter );
    this->xs_.print( iter );
    *iter++ = 'e';
    *iter++ = 'n';
    *iter++ = 'd';
    *iter++ = '\n';
  };
};

} // NDItk namespace
} // njoy namespace

#endif
