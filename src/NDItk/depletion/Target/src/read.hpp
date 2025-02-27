/*
 *  @brief Read the record data
 *
 *  @param[in,out] iter        an iterator to the current position in the input
 *  @param[in,out] end         an iterator to the end of the input 
 */
template< typename Iterator >
void read( Iterator& iter, const Iterator& end ) {
  
  std::string skip_keyword;

  this->identifier_ = njoy::tools::disco::FreeFormatInteger::read<int>( iter, end );

  // skip over "num_products" keyword (not part of record)
  skip_keyword = njoy::tools::disco::FreeFormatCharacter::read<std::string>( iter, end );
  auto numberProducts = njoy::tools::disco::FreeFormatInteger::read<int>( iter, end );

  // read in the vector of products
  this->products_.resize(numberProducts);
  for ( auto& entry : this->products_ ) {

    // skip over "product" keyword
    skip_keyword = njoy::tools::disco::FreeFormatCharacter::read<std::string>( iter, end );

    entry.read( iter, end );
  }

}
