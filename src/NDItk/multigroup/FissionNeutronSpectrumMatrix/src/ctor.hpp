/**
 *  @brief Default constructor
 */
FissionNeutronSpectrumMatrix() : RealListRecord( base::Keyword( "chi_mat" ) ) {}

/**
 *  @brief Constructor for a fission type
 *
 *  @param[in] type    the fission type (prompt, delayed or total)
 */
FissionNeutronSpectrumMatrix( FissionType type ) : RealListRecord( base::Keyword( "chi_mat", type ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] type      the fission type (prompt, delayed or total)
 *  @param[in] values    the fission neutron spectrum matrix values
 */
FissionNeutronSpectrumMatrix( FissionType type,
                              std::vector< double > values ) :
    RealListRecord( base::Keyword( "chi_mat", type ), std::move( values ) ) {

  verify( this->values() );
}
