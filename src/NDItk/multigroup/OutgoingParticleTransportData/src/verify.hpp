/**
 *  @brief Verify the outgoing transport data
 *
 *  The following verification tests are performed:
 *    - there is at least one value
 *
 *  @param[in] values    the zaid values to be verified
 */
template < typename Range >
static void verify( const Range& values ) {

  if ( values.size() < 1 ) {

    Log::error( "Expected at least one zaid value, found {}",
                values.size() );
    throw std::exception();
  }
}
