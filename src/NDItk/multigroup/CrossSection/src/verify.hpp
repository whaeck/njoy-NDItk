/**
 *  @brief Verify the cross section data values
 *
 *  The following verification tests are performed:
 *    - there are at least three values
 *    - the reaction identifier looks to be an integer
 *
 *  @param[in] data    the data values in the cross section subrecord
 */
template < typename Range >
static void verify( const Range& data ) {

  if ( data.size() < 3 ) {

    Log::error( "Expected at least 3 data values consisting of a reaction identifier,\n"
                "a Q value and at least one cross section value" );
    Log::info( "Found {} data values", data.size() );
    throw std::exception();
  }

  if ( data[0] - static_cast< int >( std::round( data[0] ) ) != 0 ) {

    Log::error( "Expected an integer value for the reaction identifier" );
    Log::info( "Found {} as the reaction identifier", data[0] );
    throw std::exception();
  }
}
