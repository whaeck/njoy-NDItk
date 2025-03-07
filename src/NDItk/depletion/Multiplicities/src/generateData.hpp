/**
 *  @brief Generate the subrecord's data vector
 *
 *  @param[in] reactionProduct      the reaction product zaid
 *  @param[in] reactionIdentifiers  the reaction MTs
 *  @param[in] multiplicities       the multiplicity values
 */
static std::vector< int >
generateData( int reactionProduct, std::vector< int > reactionIdentifiers,
                std::vector< int > multiplicities ) {

  auto size = reactionIdentifiers.size();
  if ( multiplicities.size() != size ) {

    Log::error( "The number of reaction identifiers and multiplicities "
                "is inconsistent" );
    Log::info( "Found {} reaction identifiers", reactionIdentifiers.size() );
    Log::info( "Found {} multiplicity values", multiplicities.size() );
    throw std::exception();
  }
  std::vector< int > data = { reactionProduct, static_cast< int >( size ) };
  for ( unsigned int i = 0; i < size; ++i ) {

    data.push_back( reactionIdentifiers[i] );
    data.push_back( multiplicities[i] );
  }
  return data;
}
