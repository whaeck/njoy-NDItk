/**
 *  @brief Default constructor for the primary group structure
 */
AverageFissionEnergyRelease() : RealListRecord( "fiss_q" ) {}


/**
 *  @brief Constructor for the primary group structure
 *
 *  @param[in] total       the total energy release (including delayed particles
 *                         and neutrinos)
 *  @param[in] prompt      the recoverable energy release (total minus delayed
 *                         particles and neutrinos)
 *  @param[in] neutrons    the energy release through prompt neutrons
 *  @param[in] gammas      the energy release through prompt gammas
 *  @param[in] betas       the energy release through delayed betas
 *  @param[in] fragments   the kinetic energy of fission fragments
 */
AverageFissionEnergyRelease( double total, double recoverable, double neutrons,
                             double gammas, double betas, double fragments ) :
    RealListRecord( "fiss_q", { recoverable, total, betas,
                                gammas, fragments, neutrons } ) {

  //! @todo do we want to do some verification here?
}
