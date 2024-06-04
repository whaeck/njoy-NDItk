/**
 *  @brief Constructor
 *
 *  @param[in] order      the Legendre order of the moment
 *  @param[in] values     the matrix values
 *  @param[in] incident   the number of incident groups
 *  @param[in] outgoing   the number of outgoing groups
 */
LegendreMoment( int order, std::vector< double > values,
                std::size_t incident, std::size_t outgoing ) :
  Parent( generateData( order, std::move( values ) ) ),
  incident_( incident ), outgoing_( outgoing ) {

  verify( this->values(), this->numberPrimaryGroups(), this->numberOutgoingGroups() );
}

/**
 *  @brief Constructor
 *
 *  @param[in] order      the Legendre order of the moment
 *  @param[in] values     the matrix values
 *  @param[in] incident   the number of incident groups
 */
LegendreMoment( int order, std::vector< double > values, std::size_t incident ) :
  LegendreMoment( order, std::move( values ), incident, incident ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin      the begin iterator of the cross section
 *  @param[in] end        the end iterator of the cross section
 *  @param[in] incident   the number of incident groups
 *  @param[in] outgoing   the number of outgoing groups
 */
LegendreMoment( Iterator begin, Iterator end,
                std::size_t incident, std::size_t outgoing ) :
  Parent( begin, end ),
  incident_( incident ), outgoing_( outgoing ) {

  verify( this->values(), this->numberPrimaryGroups(), this->numberOutgoingGroups() );
}

/**
 *  @brief Constructor
 *
 *  @param[in] begin      the begin iterator of the cross section
 *  @param[in] end        the end iterator of the cross section
 *  @param[in] incident   the number of incident groups
 */
LegendreMoment( Iterator begin, Iterator end, std::size_t incident ) :
  LegendreMoment( begin, end, incident, incident ) {}
