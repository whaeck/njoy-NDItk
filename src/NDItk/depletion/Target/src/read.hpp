/*
 *  @brief Read the record data
 *
 *  @param[in,out] iter        an iterator to the current position in the input
 *  @param[in,out] end         an iterator to the end of the input 
 */
template< typename Iterator >
void read( Iterator& iter, const Iterator& end ) {
  
  std::string keyword;

  // read in target particle identifier
  this->identifier_ = njoy::tools::disco::FreeFormatInteger::read<int>( iter, end );

  // "num_products" keyword (not stored as record)
  keyword = njoy::tools::disco::FreeFormatCharacter::read<std::string>( iter, end );
  if ( keyword != "num_products" ) {
    Log::error( "Expected the 'num_products' keyword as the second entry in a 'Target' record" );
    Log::info( "Found {} as a keyword instead", keyword );
  }

  // read in number of products
  auto numberProducts = njoy::tools::disco::FreeFormatInteger::read<int>( iter, end );
  if ( numberProducts <= 0 ) {
    Log::error( "Expected at least one 'Product' record in a 'Target' record" );
  }

  // read in the vector of products
  this->products_.resize(numberProducts);
  for ( auto& entry : this->products_ ) {

    // "product" keyword
    keyword = njoy::tools::disco::FreeFormatCharacter::read<std::string>( iter, end );

    if ( keyword != "product" ) {
      Log::error( "Expected the 'product' keyword as the next entry in a 'Target' record" );
      Log::info( "Found {} as a keyword instead", keyword );
    }

    // read in product and add to the data
    entry.read( iter, end );
  }

  verify( this->products() );
}
