/**
 *  @brief Read the record data
 *
 *  @param[in] iter    the current position in the input
 *  @param[in] end     the end position in the input
 *  @param[in] size    the number of values to be read
 */
template< typename Iterator >
void read( Iterator& iter, const Iterator& end, std::size_t size ) {

  std::vector< double > data;
  data.reserve( size );
  while ( size-- ) {

    data.push_back( njoy::tools::disco::FreeFormatReal::read< double >( iter, end ) );
  }
  this->data() = data;
};
