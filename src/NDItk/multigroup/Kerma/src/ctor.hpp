/**
 *  @brief Default constructor for the primary kerma
 */
Kerma() : RealListRecord( base::Keyword( "kerma" ) ) {}

/**
 *  @brief Default constructor for a secondary particle's kerma
 *
 *  @param[in] particle    the secondary particle identifier
 */
Kerma( unsigned int particle ) :
    RealListRecord( base::Keyword( "kerma", particle ) ) {}

/**
 *  @brief Constructor for the primary kerma
 *
 *  @param[in] values    the kerma values
 */
Kerma( std::vector< double > values ) :
    RealListRecord( base::Keyword( "kerma" ), std::move( values ) ) {

  verify( this->values() );
}

/**
 *  @brief Constructor for a secondary particle's kerma
 *
 *  @param[in] particle    the secondary particle identifier
 *  @param[in] values      the kerma values
 */
Kerma( unsigned int particle, std::vector< double > values ) :
    RealListRecord( base::Keyword( "kerma", particle ),
                    std::move( values ) ) {

  verify( this->values() );
}
