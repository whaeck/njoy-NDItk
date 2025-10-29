/**
 *  @brief Default constructor
 */
DosimetryTable() :
    metadata_(), primary_structure_(),
    weights_(), total_(), xs_(),
    product_multiplicities_all_( multigroup::ReactionMultiplicityType::All ),
    product_multiplicities_few_( multigroup::ReactionMultiplicityType::Few ),
    product_multiplicities_rmo_( multigroup::ReactionMultiplicityType::RMO ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] zaid              the zaid of the table
 *  @param[in] libname           the library name
 *  @param[in] process           the processing date
 *  @param[in] awr               the atomic weight ratio of the target
 *                               (with respect to the neutron mass)
 *  @param[in] temperature       the temperature of the target
 *  @param[in] dilution          the dilution (aka sigma0)
 *  @param[in] structure         the primary group structure
 *  @param[in] outgoing          the outgoing particle group structures
 *  @param[in] weights           the flux weights
 *  @param[in] total_xs          the total cross section
 *  @param[in] reaction_xs       the reaction cross section data
 *  @param[in] information       the table information line (optional)
 *  @param[in] source            the source date (optional)
 *  @param[in] weight            the atomic weight of the target (optional)
 */
DosimetryTable( std::string zaid, std::string libname,
                std::string process, double awr, double temperature,
                double dilution,
                multigroup::EnergyGroupStructure structure,
                multigroup::FluxWeights weigths,
                multigroup::TotalCrossSection total_xs,
                multigroup::ReactionCrossSections reaction_xs,
                std::optional< std::string > information = std::nullopt,
                std::optional< std::string > source = std::nullopt,
                std::optional< double > weight = std::nullopt ) :
    metadata_( std::move( zaid ), std::move( libname ),
               std::move( process ), awr, temperature, dilution,
               structure.numberGroups(), reaction_xs.numberReactions(),
               std::move( information ), std::move( source ), std::move( weight ),
               std::nullopt, std::nullopt ),
    primary_structure_( std::move( structure ) ),
    weights_( std::move( weigths ) ),
    total_( std::move( total_xs ) ),
    xs_( std::move( reaction_xs ) ) {

  this->verify();
}
