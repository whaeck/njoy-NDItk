/**
 *  @brief Default constructor
 */
MultigroupTable() :
    metadata_(), primary_structure_(),
    velocities_(), weights_(), total_(), xs_(), release_(),
    outgoing_particles_(), outgoing_structure_(),
    primary_heating_(), outgoing_heating_(),
    primary_kerma_(), outgoing_kerma_() {}

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
 *  @param[in] velocities        the group velocities
 *  @param[in] weights           the flux weights
 *  @param[in] total             the total cross section
 *  @param[in] xs                the reaction cross section data
 *  @param[in] scattering        the scattering matrix
 *  @param[in] source            the source date (optional)
 *  @param[in] weight            the atomic weight of the target (optional)
 *  @param[in] release           the average fission energy release data (optional)
 *  @param[in] types             the outgoing particle types (optional)
 *  @param[in] transport         the outgoing particle transport data (optional)
 *  @param[in] primaryHeating    the primary particle heating numbers (optional)
 *  @param[in] outgoingHeating   the outgoing particles' heating numbers (optional)
 *  @param[in] primaryKerma      the primary particle kerma (optional)
 *  @param[in] outgoingKerma     the outgoing particle kermas (optional)
 */
MultigroupTable( std::string zaid, std::string libname,
                 std::string process, double awr, double temperature,
                 double dilution,
                 multigroup::EnergyGroupStructure structure,
                 std::vector< multigroup::EnergyGroupStructure > outgoing,
                 multigroup::Velocities velocities,
                 multigroup::FluxWeights weigths,
                 multigroup::ReactionCrossSections xs,
                 multigroup::ScatteringMatrix scattering,
                 std::optional< std::string > source = std::nullopt,
                 std::optional< double > weight = std::nullopt,
                 std::optional< multigroup::TotalCrossSection > total = std::nullopt,
                 std::optional< multigroup::AverageFissionEnergyRelease > release = std::nullopt,
                 std::optional< multigroup::OutgoingParticleTypes > types = std::nullopt,
                 std::optional< multigroup::OutgoingParticleTransportData > transport = std::nullopt,
                 std::optional< multigroup::HeatingNumbers > primaryHeating = std::nullopt,
                 std::vector< multigroup::HeatingNumbers > outgoingHeating = {},
                 std::optional< multigroup::Kerma > primaryKerma = std::nullopt,
                 std::vector< multigroup::Kerma > outgoingKerma = {} ) :
    metadata_( std::move( zaid ), std::move( libname ),
               std::move( process ), awr, temperature, dilution,
               structure.numberGroups(), generateOutgoingStructureMetadata( outgoing ),
               xs.numberReactions(), scattering.numberLegendreMoments(),
               std::move( source ), std::move( weight ),
               std::nullopt, std::nullopt ),
    primary_structure_( std::move( structure ) ),
    velocities_( std::move( velocities ) ),
    outgoing_structure_( std::move( outgoing ) ),
    weights_( std::move( weigths ) ),
    xs_( std::move( xs ) ),
    scattering_( std::move( scattering ) ),
    release_( std::move( release.value() ) ),
    outgoing_heating_( std::move( outgoingHeating ) ),
    outgoing_kerma_( std::move( outgoingKerma ) ) {

  if ( total.has_value() ) {

    this->total_ = std::move( total.value() );
  }
  if ( primaryHeating.has_value() ) {

    this->primary_heating_ = std::move( primaryHeating.value() );
  }
  if ( primaryKerma.has_value() ) {

    this->primary_kerma_ = std::move( primaryKerma.value() );
  }
  if ( types.has_value() ) {

    this->outgoing_particles_ = std::move( types.value() );
  }
  if ( transport.has_value() ) {

    this->outgoing_zaids_ = std::move( transport.value() );
  }
  this->verify();
}