#ifndef NJOY_NDITK_BASE_KEYWORD
#define NJOY_NDITK_BASE_KEYWORD

// system includes
#include <optional>
#include <regex>
#include <string>
#include <iostream>

// other includes
#include "tools/Log.hpp"

namespace njoy {
namespace NDItk {
namespace base {

/**
 *  @brief A class for NDI keywords
 *
 *  This class allows us to decompose
 */
class Keyword {

  /* fields */
  std::string keyword_;
  std::optional< std::string > subtype_ = std::nullopt;
  std::optional< unsigned int > particle_ = std::nullopt;

  /* auxilairy functions */
  #include "NDItk/base/Keyword/src/splitKeyword.hpp"

public:

  /* constructor */

  #include "NDItk/base/Keyword/src/ctor.hpp"

  /**
   *  @brief Return the keyword
   */
  const std::string& keyword() const { return this->keyword_; }

  /**
   *  @brief Return whether or not the keyword has a subtype
   */
  bool hasSubtype() const { return this->subtype_.has_value(); }

  /**
   *  @brief Return the subtype (if any)
   */
  const std::optional< std::string >& subtype() const { return this->subtype_; }

  /**
   *  @brief Return the particle identifier (if any)
   */
  const std::optional< unsigned int >& particle() const { return this->particle_; }

  /**
   *  @brief Print the record keyword
   *
   *  @param[in] iter   the current position in the output
   */
  template< typename OutputIterator >
  void print( OutputIterator& iter ) const {

    for ( auto c : this->keyword() ) { *iter++ = c; }
    *iter++ = '\n';
  };
};

} // base namespace
} // NDItk namespace
} // njoy namespace

#endif
