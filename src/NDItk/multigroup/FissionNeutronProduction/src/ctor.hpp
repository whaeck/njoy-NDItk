/**
 *  @brief Default constructor
 */
FissionNeutronProduction() : RealListRecord( base::Keyword( "nu_sig_f" ) ) {}

/**
 *  @brief Constructor for a fission type
 *
 *  @param[in] type    the fission type (prompt, delayed or total)
 */
FissionNeutronProduction( FissionType type ) : RealListRecord( base::Keyword( "nu_sig_f", type ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] type      the fission type (prompt, delayed or total)
 *  @param[in] values    the fission neutron production values
 */
FissionNeutronProduction( FissionType type,
                          std::vector< double > values ) :
    RealListRecord( base::Keyword( "nu_sig_f", type ), std::move( values ) ) {

  verify( this->values() );
}
