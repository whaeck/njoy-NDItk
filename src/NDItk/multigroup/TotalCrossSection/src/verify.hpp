/**
 *  @brief Verify the weights
 *
 *  The following verification tests are performed:
 *    - there is at least one value
 *
 *  @param[in] values    the cross seciton values to be verified
 */
template < typename Range >
static void verify( const Range& values ) {

  if ( values.size() < 1 ) {

    Log::error( "Expected at least one total cross section value, found {}",
                values.size() );
    throw std::exception();
  }
}
