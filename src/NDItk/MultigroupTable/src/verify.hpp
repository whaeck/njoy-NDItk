/**
 *  @brief Verify the multigroup data
 *
 *  The following verification tests are performed:
 *    - the number of groups accross the data is consistent
 */
void verify() {

  // consistent group structure
  const auto groups = this->metadata().numberGroups().value();
  if ( ( this->primaryGroupBoundaries().numberGroups() != groups ) ||
       ( this->fluxWeights().numberGroups() != groups ) ||
       ( this->reactionCrossSections().numberGroups() != groups ) ) {

    Log::error( "Found inconsistent number of primary groups across the table" );
    Log::info( "Number of primary groups in the metadata: {}", this->metadata().numberGroups().value() );
    Log::info( "Number of primary groups in the group structure: {}", this->primaryGroupBoundaries().numberGroups() );
    Log::info( "Number of primary groups in the flux weights: {}", this->fluxWeights().numberGroups() );
    Log::info( "Number of primary groups in the reaction cross section data: {}",
               this->reactionCrossSections().numberGroups() );
    throw std::exception();
  }
};
