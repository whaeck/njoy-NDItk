#ifndef NJOY_NDITK_DEPLETION
#define NJOY_NDITK_DEPLETION

// system includes

// other includes
#include "tools/Log.hpp"
#include "NDItk/depletion/Metadata.hpp"
#include "NDItk/depletion/IncidentParticle.hpp"

namespace njoy {
namespace NDItk {

/**
 *  @brief A product/depletion table 
 */
class DepletionTable {

  /* fields */

  depletion::Metadata metadata_;
  std::vector< depletion::IncidentParticle > incident_particles_;

  /* auxiliary functions */

  #include "NDItk/DepletionTable/src/verify.hpp"

public:

  /* constructor */

  #include "NDItk/DepletionTable/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the metadata of the table
   */
  const depletion::Metadata& metadata() const { return this->metadata_; }

  /**
   *  @brief Return the number of incident particles
   */
  int numberIncidentParticles() const { return this->incident_particles_.size(); }

  /**
   *  @brief Return the record for an incident particle
   */
  const depletion::IncidentParticle&
  incidentParticle( unsigned int particle ) const {

    auto pos = std::lower_bound( this->incident_particles_.begin(),
                                 this->incident_particles_.end(),
                                 particle,
                                 [] ( auto&& left, auto&& right ) {

                                   return left.incidentIdentifier() < right;
                                 } );
    if ( pos != this->incident_particles_.end() ) {

      if ( pos->incidentIdentifier() == particle ) {

        return *pos;
      }
    }
    Log::error( "The requested incident particle \'{}\' has no associated "
                "record", particle );
    throw std::exception();
  }

  #include "NDItk/DepletionTable/src/read.hpp"

  /**
   *  @brief Print the NDI table
   *
   *  @param[in] iter   the current position in the output
   */
  template< typename OutputIterator >
  void print( OutputIterator& iter ) const {

    this->metadata_.print( iter );
    for ( const auto& entry : this->incident_particles_ ) { entry.print( iter ); }
    base::Keyword( "end" ).print( iter );
  };
};

} // NDItk namespace
} // njoy namespace

#endif
