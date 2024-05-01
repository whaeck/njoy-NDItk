/**
 *  @brief Default constructor for the primary group structure
 */
EnergyGroupStructure() : RealListRecord( "e_bounds" ) {}

/**
 *  @brief Default constructor for a secondary particle group structure
 *
 *  @param[in] particle    the secondary particle ID
 */
EnergyGroupStructure( unsigned int particle ) :
    RealListRecord( std::string( "e_bounds_" ) + std::to_string( particle ) ) {}

/**
 *  @brief Constructor for the primary group structure
 *
 *  @param[in] boundaries    the group structure boundaries
 */
EnergyGroupStructure( std::vector< double > boundaries ) :
    RealListRecord( "e_bounds", std::move( boundaries ) ) {

  verify( this->values() );
}

/**
 *  @brief Constructor for a secondary particle group structure
 *
 *  @param[in] particle      the secondary particle ID
 *  @param[in] boundaries    the group structure boundaries
 */
EnergyGroupStructure( unsigned int particle, std::vector< double > boundaries ) :
    RealListRecord( std::string( "e_bounds_" ) + std::to_string( particle ),
                    std::move( boundaries ) ) {

  verify( this->values() );
}
