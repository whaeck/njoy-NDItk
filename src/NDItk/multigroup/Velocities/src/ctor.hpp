/**
 *  @brief Default constructor
 */
Velocities() : RealListRecord( base::Keyword( "vel" ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] weights    the flux weights
 */
Velocities( std::vector< double > values ) :
    RealListRecord( base::Keyword( "vel" ), std::move( values ) ) {

  verify( this->values() );
}
