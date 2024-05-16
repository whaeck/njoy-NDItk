#ifndef NJOY_NDITK_MULTIGROUP
#define NJOY_NDITK_MULTIGROUP

// system includes

// other includes
#include "tools/Log.hpp"
#include "NDItk/multigroup/Metadata.hpp"
#include "NDItk/multigroup/EnergyGroupStructure.hpp"
#include "NDItk/multigroup/Velocities.hpp"
#include "NDItk/multigroup/FluxWeights.hpp"
#include "NDItk/multigroup/ReactionCrossSections.hpp"
#include "NDItk/multigroup/TotalCrossSection.hpp"
#include "NDItk/multigroup/AverageFissionEnergyRelease.hpp"
#include "NDItk/multigroup/HeatingNumbers.hpp"
#include "NDItk/multigroup/Kerma.hpp"

namespace njoy {
namespace NDItk {

/**
 *  @brief A multigroup neutron and photon table
 */
class MultigroupTable {

  /* fields */

  multigroup::Metadata metadata_;
  multigroup::EnergyGroupStructure primary_structure_;
  std::vector< multigroup::EnergyGroupStructure > outgoing_structure_;
  multigroup::Velocities velocities_;
  multigroup::FluxWeights weights_;
  multigroup::ReactionCrossSections xs_;
  multigroup::TotalCrossSection total_;
  multigroup::AverageFissionEnergyRelease release_;
  multigroup::HeatingNumbers primary_heating_;
  std::vector< multigroup::HeatingNumbers > outgoing_heating_;
  multigroup::Kerma primary_kerma_;
  std::vector< multigroup::Kerma > outgoing_kerma_;

  /* auxiliary functions */

  #include "NDItk/MultigroupTable/src/generateOutgoingStructureMetadata.hpp"
  #include "NDItk/MultigroupTable/src/readRecord.hpp"
  #include "NDItk/MultigroupTable/src/readPrimaryStructure.hpp"
  #include "NDItk/MultigroupTable/src/readOutgoingStructure.hpp"
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
  const multigroup::EnergyGroupStructure& primaryGroupBoundaries() const {

    return this->primary_structure_;
  }

  /**
   *  @brief Return the group structure record for an outgoing particle
   */
  const multigroup::EnergyGroupStructure&
  outgoingGroupBoundaries( unsigned int particle ) const {

    auto pos = std::lower_bound( this->outgoing_structure_.begin(),
                                 this->outgoing_structure_.end(),
                                 particle,
                                 [] ( auto&& left, auto&& right ) {

                                   return left.particle() < right;
                                 } );
    if ( pos != this->outgoing_structure_.end() ) {

      if ( pos->particle() == particle ) {

        return *pos;
      }
    }
    Log::error( "The requested outgoing particle \'{}\' has no outgoing group structure", particle );
    throw std::exception();
  }

  /**
   *  @brief Return the velocity record
   */
  const multigroup::Velocities& velocities() const {

    return this->velocities_;
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
   *  @brief Return the average fission energy release record
   */
  const multigroup::AverageFissionEnergyRelease&
  averageFissionEnergyRelease() const {

    return this->release_;
  }

  /**
   *  @brief Return the primary heating numbers record
   */
  const multigroup::HeatingNumbers& primaryHeatingNumbers() const {

    return this->primary_heating_;
  }

  /**
   *  @brief Return the heating numbers record for an outgoing particle
   */
  const multigroup::HeatingNumbers&
  outgoingHeatingNumbers( unsigned int particle ) const {

    auto pos = std::lower_bound( this->outgoing_heating_.begin(),
                                 this->outgoing_heating_.end(),
                                 particle,
                                 [] ( auto&& left, auto&& right ) {

                                   return left.particle() < right;
                                 } );
    if ( pos != this->outgoing_heating_.end() ) {

      if ( pos->particle() == particle ) {

        return *pos;
      }
    }
    Log::error( "The requested outgoing particle \'{}\' has no associated "
                "heating numbers", particle );
    throw std::exception();
  }

  /**
   *  @brief Return the primary kerma record
   */
  const multigroup::Kerma& primaryKerma() const {

    return this->primary_kerma_;
  }

  /**
   *  @brief Return the hkerma record for an outgoing particle
   */
  const multigroup::Kerma&
  outgoingKerma( unsigned int particle ) const {

    auto pos = std::lower_bound( this->outgoing_kerma_.begin(),
                                 this->outgoing_kerma_.end(),
                                 particle,
                                 [] ( auto&& left, auto&& right ) {

                                   return left.particle() < right;
                                 } );
    if ( pos != this->outgoing_kerma_.end() ) {

      if ( pos->particle() == particle ) {

        return *pos;
      }
    }
    Log::error( "The requested outgoing particle \'{}\' has no associated "
                "kerma record", particle );
    throw std::exception();
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
    this->primary_structure_.print( iter );
    for ( const auto& entry : this->outgoing_structure_ ) { entry.print( iter ); }
    this->velocities_.print( iter );
    this->weights_.print( iter );
    this->total_.print( iter );
    this->xs_.print( iter );
    this->release_.print( iter );
    this->primary_heating_.print( iter );
    for ( const auto& entry : this->outgoing_heating_ ) { entry.print( iter ); }
    this->primary_kerma_.print( iter );
    for ( const auto& entry : this->outgoing_kerma_ ) { entry.print( iter ); }
    base::Keyword( "end" ).print( iter );
  };
};

} // NDItk namespace
} // njoy namespace

#endif
