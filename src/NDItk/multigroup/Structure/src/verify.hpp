/**
 *  @brief Verify the group structure
 *
 *  The following verification tests are performed:
 *    - there are at least two values
 *    - the boundaries are unique and in descending order
 *
 *  @param[in] boundaries    the boundary values to be verified
 */
template < typename Range >
static void verify( const Range& boundaries ) {

  using namespace njoy::tools;

  if ( boundaries.size() < 2 ) {

    Log::error( "Expected at least two group structure boundary values, "
                "found {}", boundaries.size() );
    throw std::exception();
  }

  if ( ! std::is_sorted( std20::ranges::rbegin( boundaries ),
                         std20::ranges::rend( boundaries ) ) ) {

    Log::error( "The boundaries of the group structure do not appear "
                "to be in descending order" );
    throw std::exception();
  }
  if ( std::adjacent_find( std20::ranges::rbegin( boundaries ),
                           std20::ranges::rend( boundaries ) ) !=
       std20::ranges::rend( boundaries ) ) {

    Log::error( "The boundaries of the group structure do not appear "
                "to be unique" );
    throw std::exception();
  }
}
