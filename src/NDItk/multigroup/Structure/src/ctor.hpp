/**
 *  @brief Default constructor for the primary group structure
 */
Structure() : RealListRecord( "e_bounds" ) {}

/**
 *  @brief Default constructor for a secondary particle group structure
 *
 *  @param[in] particle    the secondary particle ID
 */
Structure( unsigned int particle ) :
    RealListRecord( std::string( "e_bounds_" ) + std::to_string( particle ) ) {}

/**
 *  @brief Constructor for the primary group structure
 *
 *  @param[in] boundaries    the group structure boundaries
 */
Structure( std::vector< double > boundaries ) :
    RealListRecord( "e_bounds", std::move( boundaries ) ) {}

/**
 *  @brief Constructor for a secondary particle group structure
 *
 *  @param[in] particle      the secondary particle ID
 *  @param[in] boundaries    the group structure boundaries
 */
Structure( unsigned int particle, std::vector< double > boundaries ) :
    RealListRecord( std::string( "e_bounds_" ) + std::to_string( particle ),
                    std::move( boundaries ) ) {}
