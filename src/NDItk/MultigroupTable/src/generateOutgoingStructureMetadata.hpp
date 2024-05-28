static std::map< unsigned int, unsigned int >
generateOutgoingStructureMetadata( const std::vector< multigroup::EnergyGroupStructure >& outgoing ) {

  std::map< unsigned int, unsigned int > metadata;
  for ( const auto& entry : outgoing ) {

    unsigned int particle = entry.particle().value();
    if ( metadata.find( particle ) != metadata.end() ) {

      Log::error( "Found duplicate outgoing group structure for particle \'{}\'", particle );
      throw std::exception();
    }
    metadata[ particle ] = entry.numberGroups();
  }
  return metadata;
}