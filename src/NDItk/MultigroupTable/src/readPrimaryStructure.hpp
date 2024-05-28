template< typename Iterator >
void readPrimaryStructure( Iterator& iter, const Iterator& end ) {

  if ( this->metadata_.numberGroups().has_value() ) {

    readRecord( this->primary_structure_, iter, end,
                this->metadata_.numberGroups().value() + 1 );
  }
  else {

    Log::error( "Metadata required for the \'\' record was not found", this->primary_structure_.keyword() );
    Log::info( "Required metadata is missing: number of groups in the primary group structure" );
    throw std::exception();
  }
}