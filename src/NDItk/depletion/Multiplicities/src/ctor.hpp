/**
 *  @brief Constructor
 *
 *  @param[in] 
 *  @param[in] 
 *  @param[in] multiplicities    the multiplicity values
 */
Multiplicities( int identifier, std::vector< int > reactionData,
                std::vector< int > multiplicities ) :
  Parent( generateData( identifier, std::move( reactionData ), std::move( multiplicities ) ) ) {

  verify( this->values() );
}

/**
 *  @brief Constructor
 *
 *  @param[in] begin    the begin iterator of the multiplicity section
 *  @param[in] end      the end iterator of the multiplicity section
 */
Multiplicities( Iterator begin, Iterator end ) :
  Parent( begin, end ) {

  verify( this->values() );
}
