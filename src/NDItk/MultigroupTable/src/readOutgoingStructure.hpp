template< typename Iterator >
void readOutgoingStructure( const std::string& key, Iterator& iter, const Iterator& end ) {

  base::Keyword secondary( key );
  unsigned int particle = secondary.particle().value();
  if ( this->metadata_.numberOutgoingGroups( particle ).has_value() ) {

    auto pos = std::lower_bound( this->outgoing_structure_.begin(),
                                 this->outgoing_structure_.end(),
                                 particle,
                                 [] ( auto&& left, auto&& right ) {

                                   return left.particle() < right;
                                 } );
    if ( pos != this->outgoing_structure_.end() ) {

      if ( pos->particle() == particle ) {

        Log::error( "Duplicate keyword found: \'{}\'", secondary.keyword() );
        throw std::exception();
      }
    }
    pos = this->outgoing_structure_.insert( pos, multigroup::EnergyGroupStructure( particle ) );
    readRecord( *pos, iter, end, this->metadata_.numberOutgoingGroups( particle ).value() + 1 );
  }
  else {

    Log::error( "Metadata required for the \'\' record was not found", secondary.keyword() );
    Log::info( "Required metadata is missing: number of groups in the outgoing group structure" );
    throw std::exception();
  }
}