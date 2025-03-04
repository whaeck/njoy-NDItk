/**
 *  @brief Verify the depletion data
 *
 *  The following verification tests are performed:
 *    - 
 */
void verify() {

  
  if ( this->metadata_.numberIncidentParticles() != this->numberIncidentParticles() ) {

    Log::error( "Found a different number of incident particle records than indicated in metadata" ); 
//    Log::info( "Found a different number of incident particle records ({}) than indicated in metadata ({})", 
//               this->numberIncidentParticles(), this->metadata_.numberIncidentParticles() );
    throw std::exception();
  }

  if ( this->numberIncidentParticles() <= 0 ) {

    Log::error( "Found an invalid number of incident particle records" );
//    Log::info( "Found an invalid number of incident particle records: {}", 
//               this->numberIncidentParticles() );
    throw std::exception();
  }
};
