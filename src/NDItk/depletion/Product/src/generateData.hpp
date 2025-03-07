/**
 *  @brief Generate the record's data vector
 *
 *  @param[in] multiplicities   a depletion::Multiplicities SubListRecord
 */
static std::vector< int > generateData( Multiplicities  multiplicities ) {

  // generate the data vector
  std::vector< int > data;
  data.insert( data.end(), multiplicities.begin(), multiplicities.end() );

  return data;
}
