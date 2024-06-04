/**
 *  @brief Default constructor
 */
FissionNeutronMultiplicity( FissionType type ) : RealListRecord( base::Keyword( "nu", type ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] nubar    the fission neutron multiplicities
 */
FissionNeutronMultiplicity( FissionType type,
                            std::vector< double > nubar ) :
    RealListRecord( base::Keyword( "nu", type ), std::move( nubar ) ) {

  verify( this->values() );
}
