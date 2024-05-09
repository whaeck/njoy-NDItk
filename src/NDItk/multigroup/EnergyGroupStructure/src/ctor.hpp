/**
 *  @brief Default constructor for the primary group structure
 */
EnergyGroupStructure() : RealListRecord( base::Keyword( "e_bounds" ) ) {}

/**
 *  @brief Default constructor for a secondary particle group structure
 *
 *  @param[in] particle    the secondary particle identifier
 */
EnergyGroupStructure( unsigned int particle ) :
    RealListRecord( base::Keyword( "e_bounds", particle ) ) {}

/**
 *  @brief Constructor for the primary group structure
 *
 *  @param[in] boundaries    the group structure boundaries
 */
EnergyGroupStructure( std::vector< double > boundaries ) :
    RealListRecord( base::Keyword( "e_bounds" ), std::move( boundaries ) ) {

  verify( this->values() );
}

/**
 *  @brief Constructor for a secondary particle group structure
 *
 *  @param[in] particle      the secondary particle identifier
 *  @param[in] boundaries    the group structure boundaries
 */
EnergyGroupStructure( unsigned int particle, std::vector< double > boundaries ) :
    RealListRecord( base::Keyword( "e_bounds", particle ),
                    std::move( boundaries ) ) {

  verify( this->values() );
}
