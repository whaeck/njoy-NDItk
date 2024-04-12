/**
 *  @brief Constructor
 *
 *  @param energies   the energybounds
 */
EnergyBounds( std::vector<double> energies ):
  RecordBase( std::move( energies ) ) {}

  /**
 *  @brief Constructor
 *
 *  @param in   the input stream 
 */
EnergyBounds( std::istream& in , std::size_t size):
  RecordBase(in, size, "e_bounds") {}