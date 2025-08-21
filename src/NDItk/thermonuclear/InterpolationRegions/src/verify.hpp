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

  for (int i=3; i < data.size(); ++i) {

    if ( data[i] < 1 ) {

      Log::error( "End indices must be 1-based" );
      Log::info( "Found an index of {}", data[i] );
      throw std::exception();
    }
  }

  for (int i=3; i < data.size(); ++i) {

    if ( data[i] <= data[i-2] ) {

      Log::error( "End indices must have the regions' data being sequential" );
      Log::info( "Found {} and {} adjacent ending indices", data[i-2], data[i] );
      throw std::exception();
    }
  }
}
