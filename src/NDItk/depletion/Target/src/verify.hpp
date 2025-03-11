/**
 *  @brief Verify the vector of depletion products
 * 
 *  The following verification tests are performed:
 *    - there is at least one reaction
 *
 *  @param[in] products    the depletion product vector to be verified
 */
template < typename Range >
static void verify( const Range& products ) {

  if ( products.size() < 1 ) {

    Log::error( "Expected at least one product, found {}", products.size() );
    throw std::exception();
  }
}
