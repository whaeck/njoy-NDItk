/**
 *  @brief Read the record data
 *
 *  @param[in] iter   the current position in the input
 */
template< typename Iterator >
void read( Iterator& iter, const Iterator& end, std::size_t size ) {

  std::vector< int > data;
  data.reserve( size );
  while ( size-- ) {

    data.push_back( njoy::tools::disco::FreeFormatInteger::read< int >( iter, end ) );
  }
  this->data() = data;
};
