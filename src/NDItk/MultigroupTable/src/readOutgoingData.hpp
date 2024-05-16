template< typename Record, typename Iterator >
void readOutgoingData( const std::string& key, std::vector< Record >& vector,
                       Iterator& iter, const Iterator& end ) {

  base::Keyword secondary( key );
  unsigned int particle = secondary.particle().value();
  if ( this->metadata_.numberOutgoingGroups( particle ).has_value() ) {

    auto pos = std::lower_bound( vector.begin(),
                                 vector.end(),
                                 particle,
                                 [] ( auto&& left, auto&& right ) {

                                   return left.particle() < right;
                                 } );
    if ( pos != vector.end() ) {

      if ( pos->particle() == particle ) {

        Log::error( "Duplicate keyword found: \'{}\'", secondary.keyword() );
        throw std::exception();
      }
    }
    pos = vector.insert( pos, Record( particle ) );
    readRecord( *pos, iter, end, this->metadata_.numberOutgoingGroups( particle ).value() );
  }
  else {

    Log::error( "Metadata required for the \'\' record was not found", secondary.keyword() );
    Log::info( "Required metadata is missing: number of groups in the outgoing group structure" );
    throw std::exception();
  }
}