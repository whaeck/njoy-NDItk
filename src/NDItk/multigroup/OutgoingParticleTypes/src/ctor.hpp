/**
 *  @brief Default constructor
 */
OutgoingParticleTypes() : IntegerListRecord( base::Keyword( "sec_part_types" ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] values    the outgoing particle types
 */
OutgoingParticleTypes( std::vector< int > values ) :
    IntegerListRecord( base::Keyword( "sec_part_types" ), std::move( values ) ) {

  verify( this->values() );
}
