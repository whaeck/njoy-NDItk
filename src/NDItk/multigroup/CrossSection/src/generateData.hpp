/**
 *  @brief Generate the subrecord's data vector
 *
 *  @param[in] reaction    the reaction identifier
 *  @param[in] qvalue      the reaction Q value
 *  @param[in] values      the cross section values
 */
static std::vector< double >
generateData( int reaction, double qvalue, std::vector< double > values ) {

  std::vector< double > data( std::move( values ) );
  data.insert( data.begin(), qvalue );
  data.insert( data.begin(), static_cast< double >( reaction ) );
  return data;
}
