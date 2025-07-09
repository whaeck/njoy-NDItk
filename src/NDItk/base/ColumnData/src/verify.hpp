/**
 *  @brief Verify the column data
 *
 *  The following verification tests are performed:
 *    - there are the correct number of columns
 *
 *  @param[in] data    the data values in the subrecord
 */
template < typename Range >
static void verify( const Range& data ) {

  if ( data.size() % ncol != 0 ) {

    Log::error( "The columns must have data of equal length" );
    Log::info( 
      "Found {} data points, which can not be subdivided into {} equal-length columns", 
      data.size(), ncol 
    );
    throw std::exception();
  }
}