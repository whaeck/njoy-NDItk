/**
 *  @brief Default constructor
 */
Metadata() : zaid_( base::Keyword( "zaid" ) ),
             library_name_( base::Keyword( "library_name" ) ),
             source_date_( base::Keyword( "date_source" ) ),
             process_date_( base::Keyword( "date_processed" ) ),
             awr_( base::Keyword( "awr" ) ),
             atomic_weight_( base::Keyword( "at_wgt" ) ),
             temperature_( base::Keyword( "temp" ) ),
             dilution_( base::Keyword( "sig_0" ) ),
             groups_( base::Keyword( "num_grps" ) ),
             reactions_( base::Keyword( "num_reac" ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] zaid           the zaid of the table
 *  @param[in] libname        the library name
 *  @param[in] source         the source date
 *  @param[in] process        the processing date
 *  @param[in] awr            the atomic weight ratio of the target
 *                            (with respect to the neutron mass)
 *  @param[in] weight         the atomic weight of the target
 *  @param[in] temperature    the temperature of the target
 *  @param[in] dilution       the dilution (aka sigma0)
 *  @param[in] groups         the number of groups in the primary group structure
 *  @param[in] reactions      the number of reactions defined in the table
 */
Metadata( std::string zaid, std::string libname, std::string source, std::string process,
          double awr, double weight, double temperature, double dilution,
          unsigned int groups, unsigned int reactions ) :
    zaid_( base::Keyword( "zaid" ), std::move( zaid ) ),
    library_name_( base::Keyword( "library_name" ), std::move( libname ) ),
    source_date_( base::Keyword( "date_source" ), std::move( source ) ),
    process_date_( base::Keyword( "date_processed" ), std::move( process ) ),
    awr_( base::Keyword( "awr" ), awr ),
    atomic_weight_( base::Keyword( "at_wgt" ), weight ),
    temperature_( base::Keyword( "temp" ), temperature ),
    dilution_( base::Keyword( "sig_0" ), dilution ),
    groups_( base::Keyword( "num_grps" ), groups ),
    reactions_( base::Keyword( "num_reac" ), reactions ) {}
