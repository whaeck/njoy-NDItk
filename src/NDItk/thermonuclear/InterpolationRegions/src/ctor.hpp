/**
 *  @brief Constructor
 */
InterpolationRegions() = default;
/**
 *  @brief Constructor
 *
 *  @param[in] endIndices    a vector of 1-based indices signifying the inclusive end of each region's data
 *  @param[in] interpTypes   a vector of integers specifying the interpolation type for each region
 */
InterpolationRegions( std::vector<int> endIndices, std::vector<int> interpTypes ) :
  Parent( generateData( std::move(endIndices), std::move(interpTypes) ) ) {

  verify( this->values() );
}
/**
 *  @brief Constructor
 *
 *  @param[in] begin    the begin iterator of the interpolation regions
 *  @param[in] end      the end iterator of the interpolation regions
 */
InterpolationRegions( Iterator begin, Iterator end ) :
  Parent( begin, end ) {

  verify( this->values() );
}
