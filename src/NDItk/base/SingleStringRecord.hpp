#ifndef NJOY_NDITK_SINGLESTRINGRECORD
#define NJOY_NDITK_SINGLESTRINGRECORD

// system includes
#include <string>
#include <sstream>
#include <iomanip>

// other includes
#include "tools/disco/FreeFormatCharacter.hpp"
#include "NDItk/base/SingleValueRecord.hpp"

namespace njoy {
namespace NDItk {
namespace base {

/**
 *  @brief An NDI record with a single string value
 */
class SingleStringRecord : protected SingleValueRecord< SingleStringRecord, std::string > {

  friend class SingleValueRecord< SingleStringRecord, std::string >;
  using Parent = SingleValueRecord< SingleStringRecord, std::string >;

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

    unsigned int indent = 4;
    while ( indent-- ) { *iter++ = ' '; }
    for ( auto c : this->content().value() ) { *iter++ = c; }
    *iter++ = '\n';
  };

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] keyword   the keyword of the record
   */
  SingleStringRecord( std::string keyword ) :
      SingleValueRecord( std::move( keyword ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] keyword   the keyword of the record
   *  @param[in] value     the value of the record
   */
  SingleStringRecord( std::string keyword, std::string value ) :
      SingleValueRecord( std::move( keyword ), value ) {}

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
  void read( Iterator& iter, const Iterator& end ) {

    this->content() = njoy::tools::disco::FreeFormatCharacter::read< std::string >( iter, end );
  };
};

} // base namespace
} // NDItk namespace
} // njoy namespace

#endif
