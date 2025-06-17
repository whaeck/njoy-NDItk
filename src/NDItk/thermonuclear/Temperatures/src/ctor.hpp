/**
 *  @brief Default constructor for the temperature record
 */
Temperatures() : RealListRecord( base::Keyword( "temps" ) ) {}

/**
 *  @brief Constructor for the temperature recor
 *
 *  @param[in] values    the temperature values
 */
Temperatures( std::vector< double > values ) :
    RealListRecord( base::Keyword( "temps" ), std::move( values ) ) {

  verify( this->values() );
}