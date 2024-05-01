#ifndef NJOY_NDITK_UTILITY_SPLITKEYWORD
#define NJOY_NDITK_UTILITY_SPLITKEYWORD

// system includes
#include <string>

// other includes
#include "tools/Log.hpp"

namespace njoy {
namespace NDItk {

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
  inline std::pair< std::string, std::optional< int > > 
  splitKeyword( const std::string& keyword ) {

    constexpr std::regex key{ "^([a-z]+(?:_[a-z]+)?)_([0-9]+)" };

    std::smatch match;
    if ( std::regex_match( keyword, match, key ) ) {

      return { match[0], 
               match.size() == 1 ? std::nullopt : std::stoi( match[1] };
    }

    Log::error( "Unknown keyword found: \'{}\'", keyword );
    throw std::exception();
  }

} // NDItk namespace
} // njoy namespace

#endif
