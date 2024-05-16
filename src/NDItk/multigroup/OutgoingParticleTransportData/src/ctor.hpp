/**
 *  @brief Default constructor
 */
OutgoingParticleTransportData() : StringListRecord( base::Keyword( "sec_part_zaids" ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] values    the zaid values
 */
OutgoingParticleTransportData( std::vector< std::string > values ) :
    StringListRecord( base::Keyword( "sec_part_zaids" ), std::move( values ) ) {

  verify( this->values() );
}
