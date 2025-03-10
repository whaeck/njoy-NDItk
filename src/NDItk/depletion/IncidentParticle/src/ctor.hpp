/**
 *  @brief Default constructor
 */
IncidentParticle():
  Record( base::Keyword( "inc_part" ) ), 
  identifier_(),
  targets_() {}

/**
 *  @brief Constructor
 *
 *  @param[in] identifier   The incident particle identifier
 *  @param[in] targets      A vector of depletion targets
 */
IncidentParticle( int identifier, std::vector< Target > targets ):
  Record( base::Keyword( "inc_part" ) ), 
  identifier_( identifier ),
  targets_( std::move(targets) ) {

    verify( this->targets() );
  }
