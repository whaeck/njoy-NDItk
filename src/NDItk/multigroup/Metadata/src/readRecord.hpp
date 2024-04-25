/**
 *  @brief A helper function to read a metadata record
 */
template < typename Record, typename Iterator >
static void readRecord( Record& record, Iterator& iter, const Iterator& end ) {

  if ( ! record.empty() ) {

    throw std::runtime_error( std::string( "Duplicate keyword detected: " ) + record.keyword() );
  }
  record.read( iter, end );
}
