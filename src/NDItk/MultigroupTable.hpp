#ifndef NJOY_NDITK_MULTIGROUP
#define NJOY_NDITK_MULTIGROUP

// system includes

// other includes
#include "tools/Log.hpp"
#include "NDItk/multigroup/Metadata.hpp"
#include "NDItk/multigroup/EnergyGroupStructure.hpp"
#include "NDItk/multigroup/FluxWeights.hpp"
#include "NDItk/multigroup/ReactionCrossSections.hpp"
#include "NDItk/multigroup/AverageFissionEnergyRelease.hpp"

namespace njoy {
namespace NDItk {

/**
 *  @brief A multigroup neutron and photon table
 */
class MultigroupTable {

  /* fields */

  multigroup::Metadata metadata_;
  multigroup::EnergyGroupStructure structure_;
  multigroup::FluxWeights weights_;
  multigroup::ReactionCrossSections xs_;
  multigroup::AverageFissionEnergyRelease release_;

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
  const multigroup::EnergyGroupStructure& structure() const { return this->structure_; }

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

  /**
   *  @brief Return the average fission energy release record
   */
  const multigroup::AverageFissionEnergyRelease&
  averageFissionEnergyRelease() const {

    return this->release_;
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
    this->release_.print( iter );
    *iter++ = 'e';
    *iter++ = 'n';
    *iter++ = 'd';
    *iter++ = '\n';
  };
};

} // NDItk namespace
} // njoy namespace

#endif
