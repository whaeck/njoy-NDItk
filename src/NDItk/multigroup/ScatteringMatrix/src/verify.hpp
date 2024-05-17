/**
 *  @brief Verify the scattering matrix information
 *
 *  The following verification tests are performed:
 *    - there is at least one Legendre moment
 *    - the number of groups for each moment is the same
 *    - the moments are unique
 *
 *  @param[in] moments   the moments to be verified
 */
template < typename Range >
static void verify( const Range& moments ) {

  if ( moments.size() < 1 ) {

    Log::error( "Expected at least one moment, found {}", moments.size() );
    throw std::exception();
  }

  const auto incident = moments.front().numberPrimaryGroups();
  const auto outgoing = moments.front().numberOutgoingGroups();
  for ( unsigned int i = 0; i < moments.size(); ++i ) {

    if ( moments[i].numberPrimaryGroups() != incident ) {

      Log::error( "Inconsistent number of groups detected for moment "
                  "with order \'{}\'", moments[i].order() );
      Log::info( "Expected number of primary groups: {}", incident );
      Log::info( "Found number of primary groups: {}", moments[i].numberPrimaryGroups() );
      throw std::exception();
    }
    if ( moments[i].numberOutgoingGroups() != outgoing ) {

      Log::error( "Inconsistent number of groups detected for moment "
                  "with order \'{}\'", moments[i].order() );
      Log::info( "Expected number of outgoing groups: {}", outgoing );
      Log::info( "Found number of outgoing groups: {}", moments[i].numberOutgoingGroups() );
      throw std::exception();
    }
  }
}
