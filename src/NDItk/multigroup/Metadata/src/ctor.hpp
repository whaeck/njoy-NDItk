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
             primary_groups_( base::Keyword( "num_grps" ) ),
             outgoing_particles_( base::Keyword( "num_sec_parts" ) ),
             outgoing_groups_(),
             upscatter_groups_( base::Keyword( "up_grps" ) ),
             downscatter_groups_( base::Keyword( "down_grps" ) ),
             reactions_( base::Keyword( "num_reac" ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] zaid                 the zaid of the table
 *  @param[in] libname              the library name
 *  @param[in] process              the processing date
 *  @param[in] awr                  the atomic weight ratio of the target
 *                                  (with respect to the neutron mass)
 *  @param[in] weight               the atomic weight of the target
 *  @param[in] temperature          the temperature of the target
 *  @param[in] dilution             the dilution (aka sigma0)
 *  @param[in] groups               the number of groups in the primary group structure
 *  @param[in] outgoing             the number of groups in the outgoing group structures
 *  @param[in] reactions            the number of reactions defined in the table
 *  @param[in] source               the source date (optional)
 *  @param[in] upscatter            the number of upscatter groups (optional)
 *  @param[in] downscatter          the number of downscatter groups (optional)
 */
Metadata( std::string zaid, std::string libname, std::string process,
          double awr, double temperature, double dilution,
          unsigned int groups,
          const std::map< unsigned int, unsigned int >& outgoing,
          unsigned int reactions,
          std::optional< std::string > source = std::nullopt,
          std::optional< double  > weight = std::nullopt,
          std::optional< int > upscatter = std::nullopt,
          std::optional< int > downscatter = std::nullopt ) :
    zaid_( base::Keyword( "zaid" ), std::move( zaid ) ),
    library_name_( base::Keyword( "library_name" ), std::move( libname ) ),
    source_date_( source.has_value()
                  ? base::SingleStringRecord( base::Keyword( "date_source" ), std::move( source.value() ) )
                  : base::SingleStringRecord( base::Keyword( "date_source" ) ) ),
    process_date_( base::Keyword( "date_processed" ), std::move( process ) ),
    awr_( base::Keyword( "awr" ), awr ),
    atomic_weight_( weight.has_value()
                    ? base::SingleRealRecord( base::Keyword( "at_wgt" ), weight.value() )
                    : base::SingleRealRecord( base::Keyword( "at_wgt" ) ) ),
    temperature_( base::Keyword( "temp" ), temperature ),
    dilution_( base::Keyword( "sig_0" ), dilution ),
    primary_groups_( base::Keyword( "num_grps" ), groups ),
    outgoing_particles_( outgoing.size() > 0
                         ? base::SingleIntegerRecord( base::Keyword( "num_sec_parts" ), outgoing.size() )
                         : base::SingleIntegerRecord( base::Keyword( "num_sec_parts" ) ) ),
    outgoing_groups_( generateSecondaryGroups( outgoing ) ),
    upscatter_groups_( upscatter.has_value()
                       ? base::SingleIntegerRecord( base::Keyword( "up_grps" ), upscatter.value() )
                       : base::SingleIntegerRecord( base::Keyword( "up_grps" ) ) ),
    downscatter_groups_( upscatter.has_value()
                         ? base::SingleIntegerRecord( base::Keyword( "down_grps" ), downscatter.value() )
                         : base::SingleIntegerRecord( base::Keyword( "down_grps" ) ) ),
    reactions_( base::Keyword( "num_reac" ), reactions ) {}
