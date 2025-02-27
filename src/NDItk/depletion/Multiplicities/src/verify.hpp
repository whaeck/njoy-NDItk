/**
 *  @brief 
 *
 *  @param[in] 
 */
template < typename Range >
static void verify( const Range& data ) {

  if ( data.size() < 2 ) {

    Log::error( "Expected at least 2 data values consisting of an identifier,\n"
                "and the number of reaction data" );
    Log::info( "Found {} data values", data.size() );
    throw std::exception();
  }

  if ( data[1] < 0 ) {

    Log::error( "The number of reaction data cannot be less than zero" );
    Log::info( "Found {} as the number of reaction data", data[1] );
    throw std::exception();
  }

  if ( data.size() != 2 + 2 * data[1] ) {

    Log::error( "Expected at least {} data values consisting of an identifier,\n"
                "the number of reaction data (in this case equal to {}) followed\n"
                "by {} reaction data and multiplicity value pairs",
                2 + 2 * data[1], data[1], data[1] );
    Log::info( "Found {} data values", data.size() );
    throw std::exception();
  }
}
