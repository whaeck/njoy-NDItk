/**
 *  @brief Default constructor
 */
FissionNeutronSpectrumVector() : RealListRecord( base::Keyword( "chi_vec" ) ) {}

/**
 *  @brief Constructor for a fission type
 *
 *  @param[in] type    the fission type (prompt, delayed or total)
 */
FissionNeutronSpectrumVector( FissionType type ) : RealListRecord( base::Keyword( "chi_vec", type ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] type      the fission type (prompt, delayed or total)
 *  @param[in] values    the fission neutron spectrum vector values
 */
FissionNeutronSpectrumVector( FissionType type,
                              std::vector< double > values ) :
    RealListRecord( base::Keyword( "chi_vec", type ), std::move( values ) ) {

  verify( this->values() );
}
