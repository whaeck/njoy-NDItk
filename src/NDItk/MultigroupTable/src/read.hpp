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

    if ( this->metadata_.isMetadataKey( keyword ) ) {

      this->metadata_.read( keyword, iter, end );
    }
    else if ( keyword == this->structure_.keyword() ) {

      if ( this->metadata_.numberGroups().has_value() ) {

        readRecord( this->structure_, iter, end, this->metadata_.numberGroups().value() + 1 );
      }
      else {

        throw std::runtime_error( "Required metadata is missing: number of groups in the primary group structure" );
      }
    }
    else if ( keyword == this->weights_.keyword() ) {

      if ( this->metadata_.numberGroups().has_value() ) {

        readRecord( this->weights_, iter, end, this->metadata_.numberGroups().value() );
      }
      else {

        throw std::runtime_error( "Required metadata is missing: number of groups in the primary group structure" );
      }
    }
    else if ( keyword == this->xs_.keyword() ) {

      if ( this->metadata_.numberGroups().has_value() && this->metadata_.numberReactions().has_value() ) {

        readRecord( this->xs_, iter, end, this->metadata_.numberReactions().value(), this->metadata_.numberGroups().value() );
      }
      else {

        throw std::runtime_error( "Required metadata is missing:\n"
                                  "  - number of groups in the primary group structure\n"
                                  "  - number of reactions defined in the table" );
      }
    }
    else {

      if ( keyword != "end" ) {

        throw std::runtime_error( std::string( "Unknown keyword: " ) + keyword );
      }
    }

    while ( std::isspace( *iter ) && iter != end ) {

      ++iter;
    }
  }
};
