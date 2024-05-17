private:

/**
 *  @brief Private intermediate constructor
 */
ScatteringMatrix( std::vector< LegendreMoment >&& moments,
                  unsigned int incident,
                  unsigned int outgoing,
                  unsigned int number ) :
    RealListRecord( base::Keyword( "pn_full" ), generateData( std::move( moments ) ) ),
    incident_( incident ), outgoing_( outgoing ), number_moments_( number ) {

  this->generateBlocks();
}

public:

/**
 *  @brief Default constructor
 */
ScatteringMatrix() : RealListRecord( base::Keyword( "pn_full" ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] moments   the Legendre moments of the scattering matrix
 */
ScatteringMatrix( std::vector< LegendreMoment > moments ) :
    ScatteringMatrix( std::move( moments ),
                      moments.size() == 0 ? 0 : moments.front().numberPrimaryGroups(),
                      moments.size() == 0 ? 0 : moments.front().numberOutgoingGroups(),
                      moments.size() ) {}

/**
 *  @brief Copy constructor
 */
ScatteringMatrix( const ScatteringMatrix& base ) :
    RealListRecord( base ), incident_( base.incident_ ), outgoing_( base.outgoing_ ),
    number_moments_( base.number_moments_ ) {

  this->generateBlocks();
}

/**
 *  @brief Move constructor
 */
ScatteringMatrix( ScatteringMatrix&& base ) :
    RealListRecord( std::move( base ) ), incident_( base.incident_ ), outgoing_( base.outgoing_ ),
    number_moments_( base.number_moments_ ) {

  this->generateBlocks();
}

/**
 *  @brief Copy assignment
 */
ScatteringMatrix& operator=( const ScatteringMatrix& base ) {

  new (this) ScatteringMatrix( base );
  return *this;
}

/**
 *  @brief Move assignment
 */
ScatteringMatrix& operator=( ScatteringMatrix&& base ) {

  new (this) ScatteringMatrix( std::move( base ) );
  return *this;
}
