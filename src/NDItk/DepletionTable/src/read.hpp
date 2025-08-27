/**
 *  @brief Read the table data
 *
 *  @param[in] iter   the current position in the input
 */
template< typename Iterator >
void read( Iterator& iter, const Iterator& end ) {

  auto tmp_incident = depletion::IncidentParticle(); 
  std::vector< depletion::IncidentParticle > incident_data;

  std::string keyword;
  while ( ( keyword != "end" ) && ( iter != end ) ) {

    keyword = njoy::tools::disco::FreeFormatCharacter::read< std::string >( iter, end );

    // metadata
    if ( this->metadata_.isMetadataKey( keyword ) ) {

      this->metadata_.read( keyword, iter, end );
    }
    // incident particle data 
    else if ( keyword == tmp_incident.keyword() ) {

      tmp_incident.read( iter, end );

      incident_data.push_back( tmp_incident );
    }
    // unknown or end keyword
    else {

      if ( keyword != "end" ) {

        Log::error( "Unknown keyword found: \'{}\'", keyword );
        throw std::exception();
      }
    }

    // read over whitespace or until the end
    while ( iter != end && std::isspace( *iter ) ) {

      ++iter;
    }
  }

  this->incident_particles_ = incident_data;

  this->verify();
};
