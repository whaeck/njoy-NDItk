/**
 *  @brief Verify the vector of depletion targets
 * 
 *  The following verification tests are performed:
 *    - there is at least one target
 *
 *  @param[in] targets    the depletion target vector to be verified
 */
template < typename Range >
static void verify( const Range& targets ) {

  if ( targets.size() < 1 ) {

    Log::error( "Expected at least one target, found {}", targets.size() );
    throw std::exception();
  }
}
