/**
 *  @brief Verify the depletion data
 *
 *  The following verification tests are performed:
 *    - The number of incident particles must match btw metadata and number of records read
 *    - The number of incident particle records read must be > 0
 */
void verify() {
  
  if ( this->metadata_.numberIncidentParticles() != this->numberIncidentParticles() ) {

    Log::error( "Found a different number of incident particle records than indicated in metadata" ); 
    Log::info( "IncidentParticle records found: {}", this->numberIncidentParticles() ); 
    Log::info( "incident particles in Metadata: {}", this->metadata_.numberIncidentParticles().value() );
    throw std::exception();
  }

  if ( this->numberIncidentParticles() <= 0 ) {

    Log::error( "Found an invalid number of incident particle records" );
    Log::info( "Found an invalid number of incident particle records: {}", this->numberIncidentParticles() );
    throw std::exception();
  }
};
