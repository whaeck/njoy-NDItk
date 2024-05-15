/**
 *  @brief Read the table data
 *
 *  @param[in] iter   the current position in the input
 */
template< typename Iterator >
void read( Iterator& iter, const Iterator& end ) {

  std::string keyword;
  while ( ( keyword != "end" ) && ( iter != end ) ) {

    keyword = njoy::tools::disco::FreeFormatCharacter::read< std::string >( iter, end );

    // metadata
    if ( this->metadata_.isMetadataKey( keyword ) ) {

      this->metadata_.read( keyword, iter, end );
    }
    // primary and outgoing group structure keyword
    else if ( keyword.find( this->primary_structure_.keyword() ) == 0 ) {

      if ( keyword == this->primary_structure_.keyword() ) {

        readPrimaryStructure( iter, end );
      }
      else {

        readOutgoingStructure( keyword, iter, end );
      }
    }
    // flux weights
    else if ( keyword == this->weights_.keyword() ) {

      if ( this->metadata_.numberGroups().has_value() ) {

        readRecord( this->weights_, iter, end, this->metadata_.numberGroups().value() );
      }
      else {

        Log::error( "Metadata required for the \'\' record was not found", keyword );
        Log::info( "Required metadata is missing: number of groups in the primary group structure" );
        throw std::exception();
      }
    }
    // total cross section
    else if ( keyword == this->total_.keyword() ) {

      if ( this->metadata_.numberGroups().has_value() ) {

        readRecord( this->total_, iter, end, this->metadata_.numberGroups().value() );
      }
      else {

        Log::error( "Metadata required for the \'\' record was not found", keyword );
        Log::info( "Required metadata is missing: number of groups in the primary group structure" );
        throw std::exception();
      }
    }
    // reaction cross sections
    else if ( keyword == this->xs_.keyword() ) {

      if ( this->metadata_.numberGroups().has_value() && this->metadata_.numberReactions().has_value() ) {

        readRecord( this->xs_, iter, end, this->metadata_.numberReactions().value(), this->metadata_.numberGroups().value() );
      }
      else {

        Log::error( "Metadata required for the \'\' record was not found", keyword );
        if ( ! this->metadata_.numberGroups().has_value() ) {

          Log::info( "Required metadata is missing: number of groups in the primary group structure" );
        }
        if ( ! this->metadata_.numberReactions().has_value() ) {

          Log::info( "Required metadata is missing: number of reactions" );
        }
        throw std::exception();
      }
    }
    // average fission energy release
    else if ( keyword == this->release_.keyword() ) {

      readRecord( this->release_, iter, end );
    }
    // unknown or end keyword
    else {

      if ( keyword != "end" ) {

        Log::error( "Unknown keyword found: \'{}\'", keyword );
        throw std::exception();
      }
    }

    // read over whitespace or until the end
    while ( std::isspace( *iter ) && iter != end ) {

      ++iter;
    }
  }
};
