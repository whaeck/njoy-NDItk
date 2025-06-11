/**
 *  @brief Verify the interpolation regions
 *
 *  The following verification tests are performed:
 *    - there is at least one region
 *    - there are the correct number of indices and interpolation types
 *    - the indices are valid (the data is in sequential order)
 *
 *  @param[in] data    the data values in the subrecord
 */
template < typename Range >
static void verify( const Range& data ) {

  if ( data[0] < 1 ) {

    Log::error( "The number of interpolation regions cannot be less than one" );
    Log::info( "Found {} as the number of interpolation regions", data[0] );
    throw std::exception();
  }

  if ( data.size() != 1 + 2 * data[0] ) {

    Log::error( "Expected at least {} data values consisting of \n"
                "the number of interpolation regions (in this case equal to {}) followed\n"
                "by {} index and interpolation type pairs",
                1 + 2 * data[0], data[0], data[0] );
    Log::info( "Found {} data values", data.size() );
    throw std::exception();
  }

  for (int i=3; i < data.size(); ++i) {

    if ( data[i] <= data[i-2] ) {

      Log::error( "End indices must have the regions' data being sequential" );
      Log::info( "Found {} and {} adjacent ending indices", data[i-2], data[i] );
      throw std::exception();
    }
  }
}