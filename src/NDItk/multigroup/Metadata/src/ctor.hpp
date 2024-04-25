/**
 *  @brief Default constructor
 */
Metadata() : zaid_( "zaid" ), library_name_( "library_name" ), source_date_( "date_source" ),
             process_date_( "date_processed" ), awr_( "awr" ), atomic_weight_( "at_wgt" ),
             temperature_( "temp" ), dilution_( "sig_0" ), groups_( "num_grps" ),
             reactions_( "num_reac" ) {}

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
    zaid_( "zaid", std::move( zaid ) ), library_name_( "library_name", std::move( libname ) ),
    source_date_( "date_source", std::move( source ) ),
    process_date_( "date_processed", std::move( process ) ),
    awr_( "awr", awr ), atomic_weight_( "at_wgt", weight ), temperature_( "temp", temperature ),
    dilution_( "sig_0", dilution ), groups_( "num_grps", groups ),
    reactions_( "num_reac", reactions ) {}
