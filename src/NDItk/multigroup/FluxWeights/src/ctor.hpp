/**
 *  @brief Default constructor
 */
FluxWeights() : RealListRecord( base::Keyword( "wgts" ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] weights    the flux weights
 */
FluxWeights( std::vector< double > weights ) :
    RealListRecord( base::Keyword( "wgts" ), std::move( weights ) ) {

  verify( this->values() );
}
