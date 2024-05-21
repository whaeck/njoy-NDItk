/**
 *  @brief Generate the record's data vector
 *
 *  @param[in] xs    the cross section data
 */
static std::vector< double > generateData( std::vector< CrossSection > xs ) {

  // verify the data
  verify( xs );

  // generate the data vector
  std::vector< double > data;
  const auto groups = xs.front().numberGroups();
  data.reserve( xs.size() * ( 2 + groups ) );
  for ( unsigned int i = 0; i < xs.size(); ++i ) {

    data.insert( data.end(), xs[i].begin(), xs[i].end() );
  }
  return data;
}
