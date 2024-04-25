/**
 *  @brief Verify the cross section data values
 *
 *  The following verification tests are performed:
 *    - there are at least three values
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
}
