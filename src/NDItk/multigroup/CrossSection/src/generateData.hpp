static std::vector< double > generateData( int reaction, double qvalue, std::vector< double > values ) {

  std::vector< double > data( std::move( values ) );
  data.insert( data.begin(), qvalue );
  data.insert( data.begin(), static_cast< double >( reaction ) );
  return data;
}
