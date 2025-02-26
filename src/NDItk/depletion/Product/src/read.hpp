/*
 *  @brief Read the record data
 *
 *  @param[in,out] iter        an iterator to the current position in the input
 *  @param[in,out] end         an iterator to the end of the input 
 */
template< typename Iterator >
void read( Iterator& iter, const Iterator& end ) {
  
  std::vector< int > data;
  data.push_back( njoy::tools::disco::FreeFormatInteger::read<int>( iter, end ) );
  data.push_back( njoy::tools::disco::FreeFormatInteger::read<int>( iter, end ) );
  auto numberReactions = data.back();

  for ( int i=0; i < numberReactions; ++i ) {

    data.push_back( njoy::tools::disco::FreeFormatInteger::read<int>( iter, end ) );
    data.push_back( njoy::tools::disco::FreeFormatInteger::read<int>( iter, end ) );
  }

  this->data() = data;

  this->multiplicities_ = Multiplicities( this->begin(), this->end() );
}
