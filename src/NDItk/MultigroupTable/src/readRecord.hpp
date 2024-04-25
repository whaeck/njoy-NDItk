/**
 *  @brief A helper function to read a data record
 */
template < typename Record, typename Iterator, typename... Arguments >
static void readRecord( Record& record, Iterator& iter, const Iterator& end,
                        Arguments... arguments ) {

  if ( ! record.empty() ) {

    throw std::runtime_error( std::string( "Duplicate keyword detected: " ) + record.keyword() );
  }
  record.read( iter, end, arguments... );
}
