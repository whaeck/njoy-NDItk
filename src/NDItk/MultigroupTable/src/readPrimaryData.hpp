template< typename Record, typename Iterator >
void readPrimaryData( Record& record, Iterator& iter, const Iterator& end ) {

  if ( this->metadata_.numberGroups().has_value() ) {

    readRecord( record, iter, end,
                this->metadata_.numberGroups().value() );
  }
  else {

    Log::error( "Metadata required for the \'\' record was not found", record.keyword() );
    Log::info( "Required metadata is missing: number of groups in the primary group structure" );
    throw std::exception();
  }
}