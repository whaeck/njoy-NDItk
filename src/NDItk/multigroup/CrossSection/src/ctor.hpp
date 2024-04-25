/**
 *  @brief Constructor
 *
 *  @param[in] reaction   the reaction number
 *  @param[in] qvalue     the q value
 *  @param[in] values     the cross section values
 */
CrossSection( int reaction, double qvalue, std::vector< double > values ) :
  Parent( generateData( reaction, qvalue, std::move( values ) ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin    the begin iterator of the cross section
 *  @param[in] end      the end iterator of the cross section
 */
CrossSection( Iterator begin, Iterator end ) :
  Parent( begin, end ) {}
