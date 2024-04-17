#ifndef NJOY_NDITK_BASE_RECORD
#define NJOY_NDITK_BASE_RECORD

// system includes
#include <string>

// other includes

namespace njoy {
namespace NDItk {
namespace base {

/**
 *  @brief A base class for NDI records
 */
class Record {

  /* fields */
  std::string keyword_;

protected:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] keyword   the keyword of the record
   */
  Record( std::string keyword ) : keyword_( std::move( keyword ) ) {}

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

public:

  /**
   *  @brief Return the record keyword
   */
  const std::string& keyword() const { return this->keyword_; }
};

} // disco namespace
} // tools namespace
} // njoy namespace

#endif
