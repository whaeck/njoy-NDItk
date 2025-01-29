/**
 *  @brief Constructor
 *
 *  @param[in] product           the reaction product identifier
 *  @param[in] reactions         the reaction numbers
 *  @param[in] multiplicities    the multiplicity values
 */
Product( int product, std::vector< int > reactions,
                std::vector< int > multiplicities ) :
  Parent( generateData( product, std::move( reactions ), std::move( multiplicities ) ) ) {

  verify( this->values() );
}

/**
 *  @brief Constructor
 *
 *  @param[in] begin    the begin iterator of the product data 
 *  @param[in] end      the end iterator of the product data
 */
Product( Iterator begin, Iterator end ) :
  Parent( begin, end ) {

  verify( this->values() );
}
