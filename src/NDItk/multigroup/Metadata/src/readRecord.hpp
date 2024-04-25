/**
 *  @brief A helper function to read a metadata record
 */
template < typename Record, typename Iterator >
static void readRecord( Record& record, Iterator& iter, const Iterator& end ) {

  if ( ! record.empty() ) {

    Log::error( "Duplicate keyword found: \'{}\'", record.keyword() );
    throw std::exception();
  }
  record.read( iter, end );
}
