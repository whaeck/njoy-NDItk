#ifndef NJOY_NDITK_MULTIGROUP
#define NJOY_NDITK_MULTIGROUP

// system includes

// other includes
#include "tools/Log.hpp"
#include "NDItk/dosimetry/Metadata.hpp"
#include "NDItk/multigroup/ReactionMultiplicities.hpp"
#include "NDItk/multigroup/EnergyGroupStructure.hpp"
#include "NDItk/multigroup/FluxWeights.hpp"
#include "NDItk/multigroup/ReactionCrossSections.hpp"
#include "NDItk/multigroup/TotalCrossSection.hpp"

namespace njoy {
namespace NDItk {

/**
 *  @brief A multigroup neutron and photon table
 */
class DosimetryTable {

  /* fields */

  dosimetry::Metadata metadata_;
  multigroup::EnergyGroupStructure primary_structure_;
  multigroup::FluxWeights weights_;
  multigroup::TotalCrossSection total_;
  multigroup::ReactionCrossSections xs_;
  multigroup::ReactionMultiplicities product_multiplicities_all_;
  multigroup::ReactionMultiplicities product_multiplicities_few_;
  multigroup::ReactionMultiplicities product_multiplicities_rmo_;

  /* auxiliary functions */

  // code blatantly taken from MultigroupTable
  #include "NDItk/MultigroupTable/src/readRecord.hpp"
  #include "NDItk/MultigroupTable/src/readPrimaryStructure.hpp"
  #include "NDItk/MultigroupTable/src/readPrimaryData.hpp"

  #include "NDItk/DosimetryTable/src/verify.hpp"

public:

  /* constructor */

  #include "NDItk/DosimetryTable/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the metadata of the table
   */
  const dosimetry::Metadata& metadata() const { return this->metadata_; }

  /**
   *  @brief Return the primary group structure record
   */
  const multigroup::EnergyGroupStructure& primaryGroupBoundaries() const {

    return this->primary_structure_;
  }

  /**
   *  @brief Return the flux weight record
   */
  const multigroup::FluxWeights& fluxWeights() const { return this->weights_; }

  /**
   *  @brief Return the total cross section record
   */
  const multigroup::TotalCrossSection& totalCrossSection() const {

    return this->total_;
  }

  /**
   *  @brief Return the reaction cross section record
   */
  const multigroup::ReactionCrossSections& reactionCrossSections() const {

    return this->xs_;
  }

  /**
   *  @brief Return the reaction product multipliciies record for the requested multiplicity type
   */
  const multigroup::ReactionMultiplicities&
  reactionProductMultiplicities( const multigroup::ReactionMultiplicityType& type ) const {

    switch ( type ) {

      case multigroup::ReactionMultiplicityType::All  : return this->product_multiplicities_all_;
      case multigroup::ReactionMultiplicityType::Few  : return this->product_multiplicities_few_;
      case multigroup::ReactionMultiplicityType::RMO  : return this->product_multiplicities_rmo_;
      default : {

        throw std::runtime_error( "This code is unreachable, contact a developer" );
      }
    }
  }

  #include "NDItk/DosimetryTable/src/read.hpp"

  /**
   *  @brief Print the NDI table
   *
   *  @param[in] iter   the current position in the output
   */
  template< typename OutputIterator >
  void print( OutputIterator& iter ) const {

    this->metadata_.print( iter );
    this->primary_structure_.print( iter );
    this->weights_.print( iter );
    this->total_.print( iter );
    this->xs_.print( iter );
    this->product_multiplicities_all_.print( iter );
    this->product_multiplicities_few_.print( iter );
    this->product_multiplicities_rmo_.print( iter );
    base::Keyword( "end" ).print( iter );
  };
};

} // NDItk namespace
} // njoy namespace

#endif
