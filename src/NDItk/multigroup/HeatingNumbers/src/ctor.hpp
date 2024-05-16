/**
 *  @brief Default constructor for the primary heating numbers
 */
HeatingNumbers() : RealListRecord( base::Keyword( "heating" ) ) {}

/**
 *  @brief Default constructor for a secondary particle's heating numbers
 *
 *  @param[in] particle    the secondary particle identifier
 */
HeatingNumbers( unsigned int particle ) :
    RealListRecord( base::Keyword( "heating", particle ) ) {}

/**
 *  @brief Constructor for the primary heating numbers
 *
 *  @param[in] values    the heating numbers
 */
HeatingNumbers( std::vector< double > values ) :
    RealListRecord( base::Keyword( "heating" ), std::move( values ) ) {

  verify( this->values() );
}

/**
 *  @brief Constructor for a secondary particle's heating numbers
 *
 *  @param[in] particle    the secondary particle identifier
 *  @param[in] values      the heating numbers
 */
HeatingNumbers( unsigned int particle, std::vector< double > values ) :
    RealListRecord( base::Keyword( "heating", particle ),
                    std::move( values ) ) {

  verify( this->values() );
}
