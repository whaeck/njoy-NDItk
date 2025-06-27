/**
 *  @brief Generate the subrecord's data vector
 *
 *  @param[in] endIndices    a vector of 1-based indices signifying the inclusive end of each region's data
 *  @param[in] interpTypes   a vector of integers specifying the interpolation type for each region
 */
static std::vector< int >
generateData( std::vector<int> endIndices, std::vector<int> interpTypes ) {
              
  auto size = endIndices.size();

  if ( interpTypes.size() != size ) {

    Log::error( "The number of indices and interpolation types is inconsistent" );
    Log::info( "Found {} reaction indices", endIndices.size() );
    Log::info( "Found {} interpolation types", interpTypes.size() );
    throw std::exception();
  }

  std::vector< int > data = { static_cast< int >( size ) };

  for ( unsigned int i = 0; i < size; ++i ) {

    data.push_back( endIndices[i] );
    data.push_back( interpTypes[i] );
  }

  return data;
}
