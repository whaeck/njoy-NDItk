/**
 *  @brief Generate the subrecord's data vector
 *
 *  @param[in] product           the reaction product identifier
 *  @param[in] reactions         the reaction numbers
 *  @param[in] multiplicities    the multiplicity values
 */
static std::vector< int >
generateData( int product, std::vector< int > reactions,
              std::vector< int > multiplicities ) {

  auto size = reactions.size();
  if ( multiplicities.size() != size ) {

    Log::error( "The number of reaction identifiers and multiplicities "
                "is inconsistent" );
    Log::info( "Found {} reaction identifiers", reactions.size() );
    Log::info( "Found {} multiplicity values", multiplicities.size() );
    throw std::exception();
  }
  std::vector< int > data = { product, static_cast< int >( size ) };
  for ( unsigned int i = 0; i < size; ++i ) {

    data.push_back( reactions[i] );
    data.push_back( multiplicities[i] );
  }
  return data;
}
