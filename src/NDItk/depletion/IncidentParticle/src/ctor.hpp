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
 *  @param[in] 
 *  @param[in] 
 */
IncidentParticle( int incident_identifier, std::vector< Target > targets ):
  Record( base::Keyword( "inc_part" ) ), 
  identifier_( incident_identifier ),
  targets_( std::move(targets) ) {}
