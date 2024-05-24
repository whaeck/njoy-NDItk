/**
 *  @brief A helper function to generate the secondary group recors
 */
static std::vector< base::SingleIntegerRecord >
generateSecondaryLegendreOrder( const std::map< unsigned int, unsigned int >& outgoing ) {

  std::vector< base::SingleIntegerRecord > data;
  data.reserve( outgoing.size() );
  for ( auto&& entry : outgoing ) {

    data.emplace_back( base::Keyword( "pn_order", entry.first ), entry.second );
  }
  return data;
}
