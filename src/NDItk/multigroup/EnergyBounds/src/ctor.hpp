/**
 *  @brief Constructor
 *
 *  @param energies   the energybounds
 */
EnergyBounds( std::vector<double> energies ) :
  RecordBase( std::move( energies ) ) {}

/**
 *  @brief Constructor
 *
 *  @param in   the input stream
 */
template < typename Iterator >
EnergyBounds( Iterator& iter, const Iterator& end, std::size_t size ) :
  RecordBase( "e_bounds", iter, end, size ) {}