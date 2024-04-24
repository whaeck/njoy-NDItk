/**
 *  @brief Default constructor
 */
FluxWeights() : RealListRecord( "wgts" ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] weights    the flux weights
 */
FluxWeights( std::vector< double > weights ) :
    RealListRecord( "wgts", std::move( weights ) ) {}
