/**
 *  @brief Verify the reaction cross section information
 *
 *  The following verification tests are performed:
 *    - there is at least one reaction
 *    - the number of groups for each reaction is the same
 *
 *  @param[in] reactions    the reactions to be verified
 */
template < typename Range >
static void verify( const Range& reactions ) {

  if ( reactions.size() < 1 ) {

    Log::error( "Expected at least one reaction, found {}", reactions.size() );
    throw std::exception();
  }

  const auto groups = reactions.front().numberGroups();
  for ( unsigned int i = 0; i < reactions.size(); ++i ) {

    if ( reactions[i].numberGroups() != groups ) {

      Log::error( "Inconsistent number of groups detected for reaction "
                  "with identifier \'{}\'", reactions[i].identifier() );
      Log::info( "Expected number of groups: ", groups );
      Log::info( "Found number of groups: ", reactions[i].numberGroups() );
      throw std::exception();
    }
  }
}
