/**
 *  @brief Default constructor
 */
Metadata() : zaid_( base::Keyword( "zaid" ) ),
             information_(),
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
             legendre_order_( base::Keyword( "pn_order" ) ),
             outgoing_legendre_order_(),
             upscatter_groups_( base::Keyword( "up_grps" ) ),
             downscatter_groups_( base::Keyword( "down_grps" ) ),
             number_reactions_( base::Keyword( "num_reac" ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] zaid                 the zaid of the table
 *  @param[in] libname              the library name
 *  @param[in] process              the processing date
 *  @param[in] awr                  the atomic weight ratio of the target
 *                                  (with respect to the neutron mass)
 *  @param[in] temperature          the temperature of the target
 *  @param[in] dilution             the dilution (aka sigma0)
 *  @param[in] groups               the number of groups in the primary group structure
 *  @param[in] outgoing_groups      the number of groups in the outgoing group structures
 *  @param[in] reactions            the number of reactions defined in the table
 *  @param[in] legendre             the number of legendre moments in the scattering matrix
 *  @param[in] outgoing_groups      the number of legendre moments in the outgoing
 *                                  production matrices
 *  @param[in] information          the table information line (optional)
 *  @param[in] source               the source date (optional)
 *  @param[in] weight               the atomic weight of the target (optional)
 *  @param[in] upscatter            the number of upscatter groups (optional)
 *  @param[in] downscatter          the number of downscatter groups (optional)
 */
Metadata( std::string zaid, std::string libname, std::string process,
          double awr, double temperature, double dilution,
          unsigned int groups,
          unsigned int reactions, unsigned int legendre,
          const std::map< unsigned int, unsigned int >& outgoing_groups,
          const std::map< unsigned int, unsigned int >& outgoing_legendre,
          std::optional< std::string > information = std::nullopt,
          std::optional< std::string > source = std::nullopt,
          std::optional< double  > weight = std::nullopt,
          std::optional< int > upscatter = std::nullopt,
          std::optional< int > downscatter = std::nullopt ) :
    zaid_( base::Keyword( "zaid" ), std::move( zaid ) ),
    information_( information.has_value()
                  ? base::InformationRecord( std::move( information.value() ) )
                  : base::InformationRecord() ),
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
    outgoing_particles_( outgoing_groups.size() > 0
                         ? base::SingleIntegerRecord( base::Keyword( "num_sec_parts" ), outgoing_groups.size() )
                         : base::SingleIntegerRecord( base::Keyword( "num_sec_parts" ) ) ),
    outgoing_groups_( generateSecondaryGroups( outgoing_groups ) ),
    legendre_order_( base::SingleIntegerRecord( base::Keyword( "pn_order" ), legendre ) ),
    outgoing_legendre_order_( generateSecondaryLegendreOrder( outgoing_legendre ) ),
    upscatter_groups_( upscatter.has_value()
                       ? base::SingleIntegerRecord( base::Keyword( "up_grps" ), upscatter.value() )
                       : base::SingleIntegerRecord( base::Keyword( "up_grps" ) ) ),
    downscatter_groups_( upscatter.has_value()
                         ? base::SingleIntegerRecord( base::Keyword( "down_grps" ), downscatter.value() )
                         : base::SingleIntegerRecord( base::Keyword( "down_grps" ) ) ),
    number_reactions_( base::Keyword( "num_reac" ), reactions ) {}
