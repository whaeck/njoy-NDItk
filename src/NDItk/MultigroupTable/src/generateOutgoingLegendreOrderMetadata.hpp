static std::map< unsigned int, unsigned int >
generateOutgoingLegendreOrderMetadata( const std::vector< multigroup::ScatteringMatrix >& production ) {

  std::map< unsigned int, unsigned int > metadata;
  for ( const auto& entry : production ) {

    unsigned int particle = entry.particle().value();
    if ( metadata.find( particle ) != metadata.end() ) {

      Log::error( "Found duplicate number of Legendre moments for outgoing particle \'{}\'", particle );
      throw std::exception();
    }
    metadata[ particle ] = entry.numberLegendreMoments();
  }
  return metadata;
}