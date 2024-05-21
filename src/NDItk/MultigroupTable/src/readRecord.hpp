/**
 *  @brief A helper function to read a data record
 */
template < typename Record, typename Iterator, typename... Arguments >
static void readRecord( Record& record, Iterator& iter, const Iterator& end,
                        Arguments... arguments ) {

  if ( ! record.empty() ) {

    Log::error( "Duplicate keyword found: \'{}\'", record.keyword() );
    throw std::exception();
  }
  record.read( iter, end, arguments... );
}
