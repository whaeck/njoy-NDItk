/**
 *  @brief Generate the subrecord's data vector
 *
 *  @param[in] 
 *  @param[in] 
 *  @param[in] multiplicities    the multiplicity values
 */
static std::vector< int >
generateData( int identifier, std::vector< int > reactionData,
              std::vector< int > multiplicities ) {

  auto size = reactionData.size();
  if ( multiplicities.size() != size ) {

    Log::error( "The number of reaction data and multiplicities "
                "is inconsistent" );
    Log::info( "Found {} reaction data", reactionData.size() );
    Log::info( "Found {} multiplicity values", multiplicities.size() );
    throw std::exception();
  }
  std::vector< int > data = { identifier, static_cast< int >( size ) };
  for ( unsigned int i = 0; i < size; ++i ) {

    data.push_back( reactionData[i] );
    data.push_back( multiplicities[i] );
  }
  return data;
}
