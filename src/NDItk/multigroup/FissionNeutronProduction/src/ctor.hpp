/**
 *  @brief Default constructor
 */
FissionNeutronProduction( FissionType type ) : RealListRecord( base::Keyword( "nu_sig_f", type ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] weights    the flux weights
 */
FissionNeutronProduction( FissionType type,
                          std::vector< double > values ) :
    RealListRecord( base::Keyword( "nu_sig_f", type ), std::move( values ) ) {

  verify( this->values() );
}
