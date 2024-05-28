/**
 *  @brief Default constructor
 */
TotalCrossSection() : RealListRecord( base::Keyword( "sig_tot" ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] weights    the flux weights
 */
TotalCrossSection( std::vector< double > values ) :
    RealListRecord( base::Keyword( "sig_tot" ), std::move( values ) ) {

  verify( this->values() );
}
