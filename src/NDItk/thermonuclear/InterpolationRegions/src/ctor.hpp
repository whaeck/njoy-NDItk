/**
 *  @brief Constructor
 */
InterpolationRegions() = default;

/**
 *  @brief Constructor
 *
 *  @param[in] begin    the begin iterator of the cross section
 *  @param[in] end      the end iterator of the cross section
 */
InterpolationRegions( Iterator begin, Iterator end ) :
  Parent( begin, end ) {

  verify( this->values() );
}
