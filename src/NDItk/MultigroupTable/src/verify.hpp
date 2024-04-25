/**
 *  @brief Verify the multigroup data
 *
 *  The following verification tests are performed:
 *    - the number of groups accross the data is consistent
 */
void verify() {

  // consistent group structure
  const auto groups = this->metadata().numberGroups().value();
  if ( ( this->structure().numberGroups() != groups ) ||
       ( this->flux().numberGroups() != groups ) ||
       ( this->reactionCrossSections().numberGroups() != groups ) ) {

    Log::error( "Found inconsistent number of primary groups across the table" );
    Log::info( "Number of primary groups in the metadata: {}", this->metadata().numberGroups().value() );
    Log::info( "Number of primary groups in the structure: {}", this->structure().numberGroups() );
    Log::info( "Number of primary groups in the flux weights: {}", this->flux().numberGroups() );
    Log::info( "Number of primary groups in the reaction cross section data: {}",
               this->reactionCrossSections().numberGroups() );
    throw std::exception();
  }
};
