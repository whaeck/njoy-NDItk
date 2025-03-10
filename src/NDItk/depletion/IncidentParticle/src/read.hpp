/*
 *  @brief Read the record data
 *
 *  @param[in,out] iter        an iterator to the current position in the input
 *  @param[in,out] end         an iterator to the end of the input 
 */
template< typename Iterator >
void read( Iterator& iter, const Iterator& end ) {
  
  std::string keyword;

  // read in incident particle identifier
  this->identifier_ = njoy::tools::disco::FreeFormatInteger::read<int>( iter, end );

  // "num_targets" keyword (not stored of record)
  keyword = njoy::tools::disco::FreeFormatCharacter::read<std::string>( iter, end );
  if ( keyword != "num_targets" ) {
    Log::error( "Expected the 'num_targets' keyword as the second entry in an 'IncidentParticle' record" );
    Log::info( "Found {} as a keyword instead", keyword );
  }

  // read in number of targets
  auto numberTargets = njoy::tools::disco::FreeFormatInteger::read<int>( iter, end );
  if ( numberTargets <= 0 ) {
    Log::error( "Expected at least one 'Target' record in an 'IncidentParticle' record" );
  }

  // read in the vector of targets
  this->targets_.resize(numberTargets);
  for ( auto& entry : this->targets_ ) {

    // "target" keyword
    keyword = njoy::tools::disco::FreeFormatCharacter::read<std::string>( iter, end );

    if ( keyword != "target" ) {
      Log::error( "Expected the 'target' keyword as the next entry in an 'IncidentParticle' record" );
      Log::info( "Found {} as a keyword instead", keyword );
    }

    // read in target and add to the data
    entry.read( iter, end );
  }

  verify( this->targets() );
}
