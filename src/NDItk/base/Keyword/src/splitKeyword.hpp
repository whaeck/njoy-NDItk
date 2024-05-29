/**
 *  @brief Utility function to extract the particle id from a keyword
 *
 *  Some NDI records use keywords that include a particle id at the end of
 *  the keyword. These are basically of the form xxxxxxxx_yyyyy where yyyyy
 *  are digits that represent the particle id (e.g. 0 for gammas and 1001 for
 *  protons).
 *
 *  @param[in] keyword   the keyword
 */
static std::tuple< std::string, std::optional< std::string >, std::optional< int > >
splitKeyword( std::string keyword ) {

  // special cases: sig_0
  if ( "sig_0" == keyword ) {

    return { std::move( keyword ), std::nullopt, std::nullopt };
  }
  else {

    const std::regex key{ "^([a-z]+(?:_[a-z]+)*)(?:_([0-9]+))?" };

    std::smatch match;
    if ( std::regex_match( keyword, match, key ) ) {

      if ( match[1] == keyword ) {

        return { std::move( keyword ), std::nullopt, std::nullopt };
      }
      else {

        return { std::move( keyword ),
                 std::make_optional( std::string( match[1] ) ),
                 std::make_optional( std::stoi( match[2] ) ) };
      }
    }

    Log::error( "Unknown keyword found: \'{}\'", keyword );
    throw std::exception();
  }
}
