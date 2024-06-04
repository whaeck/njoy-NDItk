/**
 *  @brief Default constructor
 */
FissionNeutronProduction( FissionType type ) : RealListRecord( base::Keyword( "nu_sig_f", type ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] production    the fission neutron production values
 */
FissionNeutronProduction( FissionType type,
                          std::vector< double > production ) :
    RealListRecord( base::Keyword( "nu_sig_f", type ), std::move( production ) ) {

  verify( this->values() );
}
