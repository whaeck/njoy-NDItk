/**
 *  @brief Verify the weights
 *
 *  The following verification tests are performed:
 *    - there is at least one value
 *
 *  @param[in] weights    the weight values to be verified
 */
template < typename Range >
static void verify( const Range& weights ) {

  if ( weights.size() < 1 ) {

    Log::error( "Expected at least one flux weight value, found {}",
                weights.size() );
    throw std::exception();
  }
}
