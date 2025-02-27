/**
 *  @brief Default constructor
 */
Metadata() : zaid_( base::Keyword( "zaid" ) ),
             information_( ),
             library_name_( base::Keyword( "library_name" ) ),
             source_date_( base::Keyword( "date_source" ) ),
             process_date_( base::Keyword( "date_processed" ) ),
             number_incident_( base::Keyword( "num_inc_parts" ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] zaid                 the zaid of the table
 *  @param[in] libname              the library name
 *  @param[in] process              the processing date
 *  @param[in] incident             the number of incident particles
 *  @param[in] information          the table information line (optional)
 *  @param[in] source               the source date (optional)
 */
Metadata( std::string zaid, std::string libname, std::string process, int incident,
          std::optional< std::string > information = std::nullopt,
          std::optional< std::string > source = std::nullopt ):
    zaid_( base::Keyword( "zaid" ), std::move( zaid ) ),
    information_( information.has_value()
                  ? base::InformationRecord( std::move( information.value() ) )
                  : base::InformationRecord() ),
    library_name_( base::Keyword( "library_name" ), std::move( libname ) ),
    source_date_( source.has_value()
                  ? base::SingleStringRecord( base::Keyword( "date_source" ), std::move( source.value() ) )
                  : base::SingleStringRecord( base::Keyword( "date_source" ) ) ),
    process_date_( base::Keyword( "date_processed" ), std::move( process ) ),
    number_incident_( base::Keyword( "num_inc_parts" ), incident ) {}
