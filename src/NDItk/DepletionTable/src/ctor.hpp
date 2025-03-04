/**
 *  @brief Default constructor
 */
DepletionTable() :
    metadata_(), incident_particles_() {}

/**
 *  @brief Constructor
 *
 *  @param[in] zaid              the zaid of the table
 *  @param[in] libname           the library name
 *  @param[in] process           the processing date
 *  @param[in] incident          the incident particles
 *  @param[in] information       the table information line (optional)
 *  @param[in] source            the source date (optional)
 */
DepletionTable( std::string zaid, 
                 std::string libname,
                 std::string process, 
                 std::vector< depletion::IncidentParticle > incident,
                 std::optional< std::string > information = std::nullopt,
                 std::optional< std::string > source = std::nullopt ) :
    metadata_( std::move( zaid ), 
               std::move( libname ),
               std::move( process ), 
               incident.size(),
               std::move( information ), 
               std::move( source ) ),
    incident_particles_( std::move( incident ) ) {

  this->verify();
}
