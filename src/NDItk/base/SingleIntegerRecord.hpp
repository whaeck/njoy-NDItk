#ifndef NJOY_NDITK_SINGLEINTEGERRECORD
#define NJOY_NDITK_SINGLEINTEGERRECORD

// system includes
#include <sstream>
#include <iomanip>

// other includes
#include "NDItk/base/SingleValueRecord.hpp"

namespace njoy {
namespace NDItk {
namespace base {

/**
 *  @brief An NDI record with a single value
 */
class SingleIntegerRecord : protected SingleValueRecord< SingleIntegerRecord, int > {

  using Parent = SingleValueRecord< SingleIntegerRecord, int >;

protected:

  /**
   *  @brief Write the record content
   *
   *  This assumes that the content is defined.
   *
   *  @param[in] iter   the current position in the output
   */
  template< typename OutputIterator >
  void write( OutputIterator& iter ) const {

    std::ostringstream buffer;
    buffer << std::setw( 12 ) << std::right << this->content().value();
    for ( auto c : buffer.str() ) { *iter++ = c; }
    *iter++ = '\n';
  };

public:

  /* constructor */

  using Parent::Parent;

  /* methods */

  using Parent::keyword;
  using Parent::content;
  using Parent::print;

  /**
   *  @brief Read the record content
   *
   *  @param[in] iter   the current position in the input
   */
  template< typename Iterator >
  void read( Iterator& iter, const Iterator& end ) const {

    this->content() = njoy::tools::disco::FreeFormatInteger::read( iter, end );
  };
};

} // disco namespace
} // tools namespace
} // njoy namespace

#endif
