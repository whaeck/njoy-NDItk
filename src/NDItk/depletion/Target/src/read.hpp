/*
 *  @brief Read the record data
 *
 *  @param[in,out] iter        an iterator to the current position in the input
 *  @param[in,out] end         an iterator to the end of the input 
 */
template< typename Iterator >
void read( Iterator& iter, const Iterator& end ) {
  
  std::string skip_keyword;

  this->target_identifier_ = njoy::tools::disco::FreeFormatInteger::read<unsigned int>( iter, end );

  // skip over "num_products" keyword (not part of record)
  skip_keyword = njoy::tools::disco::FreeFormatCharacter::read<std::string>( iter, end );

  auto number_products = njoy::tools::disco::FreeFormatInteger::read<int>( iter, end );

  for ( size_t i=0; i < number_products; ++i ) {

    // skip over "product" keyword (not part of record)
    skip_keyword = njoy::tools::disco::FreeFormatCharacter::read<std::string>( iter, end );

    auto product_identifier = njoy::tools::disco::FreeFormatInteger::read<int>( iter, end );
    auto number_reactions   = njoy::tools::disco::FreeFormatInteger::read<int>( iter, end );

    std::vector< int > reactions;
    std::vector< int > multiplicities;
    
    for ( size_t j=0; j < number_reactions; ++j ) {

      reactions.push_back( njoy::tools::disco::FreeFormatInteger::read<int>( iter, end ) );
      multiplicities.push_back( njoy::tools::disco::FreeFormatInteger::read<int>( iter, end ) );
    } 
  
    // product will own the data
    this->products_.emplace_back( product_identifier, reactions, multiplicities );
  }

}
