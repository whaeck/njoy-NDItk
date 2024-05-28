#ifndef NJOY_NDITK_BASE_RECORD
#define NJOY_NDITK_BASE_RECORD

// system includes
#include <string>

// other includes
#include "NDItk/base/Keyword.hpp"

namespace njoy {
namespace NDItk {
namespace base {

/**
 *  @brief A base class for NDI records
 */
class Record {

  /* fields */
  Keyword keyword_;

protected:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] keyword   the keyword of the record
   */
  Record( Keyword keyword ) : keyword_( std::move( keyword ) ) {}

  /**
   *  @brief Print the record keyword
   *
   *  @param[in] iter   the current position in the output
   */
  template< typename OutputIterator >
  void print( OutputIterator& iter ) const {

    this->keyword_.print( iter );
  };

  /**
   *  @brief Return the keyword object
   */
  const Keyword& key() const { return this->keyword_; }

public:

  /**
   *  @brief Return the record keyword
   */
  const std::string& keyword() const { return this->key().keyword(); }

  /**
   *  @brief Return the subtype (if any)
   */
  const std::optional< std::string >& subtype() const { return this->key().subtype(); }

  /**
   *  @brief Return the particle identifier (if any)
   */
  const std::optional< unsigned int >& particle() const { return this->key().particle(); }
};

} // base namespace
} // NDItk namespace
} // njoy namespace

#endif
