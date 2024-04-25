/**
 *  @brief Generate the record's data vector
 *
 *  @param[in] xs    the cross section data
 */
static std::vector< double > generateData( std::vector< CrossSection > xs ) {

  std::vector< double > data;
  data.reserve( xs.size() * ( 2 + xs.front().numberGroups() ) );
  for ( auto&& entry : xs ) {

    data.insert( data.end(), entry.begin(), entry.end() );
  }
  return data;
}
