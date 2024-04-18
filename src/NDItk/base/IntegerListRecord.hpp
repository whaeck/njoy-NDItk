#ifndef NJOY_NDITK_INTEGERLISTRECORD
#define NJOY_NDITK_INTEGERLISTRECORD

// system includes
#include <vector>
#include <sstream>
#include <iomanip>

// other includes
#include "tools/disco/FreeFormatInteger.hpp"
#include "NDItk/base/ListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace base {

/**
 *  @brief An NDI record with a list of integer values
 */
class IntegerListRecord : protected ListRecord< IntegerListRecord, int > {

  friend class ListRecord< IntegerListRecord, int >;
  using Parent = ListRecord< IntegerListRecord, int >;

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

    auto full = this->content().value().size() / 6;
    auto partial = this->content().value().size() - full * 6;
    auto x = this->content().value().begin();

    while ( full-- ) {

      buffer << std::setw( 10 ) << std::right << x[0];
      buffer << std::setw( 10 ) << std::right << x[1];
      buffer << std::setw( 10 ) << std::right << x[2];
      buffer << std::setw( 10 ) << std::right << x[3];
      buffer << std::setw( 10 ) << std::right << x[4];
      buffer << std::setw( 10 ) << std::right << x[5] << '\n';
      x += 6;
    }

    if ( partial ) {

      while ( partial-- ) {

        buffer << std::setw( 10 ) << std::right << *x;
        ++x;
      }
      buffer << '\n';
    }

    for ( auto c : buffer.str() ) { *iter++ = c; }
  };

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] keyword   the keyword of the record
   */
  IntegerListRecord( std::string keyword ) :
      ListRecord( std::move( keyword ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] keyword   the keyword of the record
   *  @param[in] value     the value of the record
   */
  IntegerListRecord( std::string keyword, std::vector< int > value ) :
      ListRecord( std::move( keyword ), std::move( value ) ) {}

  /* methods */

  using Parent::keyword;
  using Parent::content;
  using Parent::hasContent;
  using Parent::print;

  /**
   *  @brief Read the record content
   *
   *  @param[in] iter   the current position in the input
   */
  template< typename Iterator >
  void read( Iterator& iter, const Iterator& end, std::size_t size ) {

    std::vector< int > data;
    data.reserve( size );
    while ( size-- ) {

      data.push_back( njoy::tools::disco::FreeFormatInteger::read< int >( iter, end ) );
    }
    this->content() = data;
  };
};

} // base namespace
} // NDItk namespace
} // njoy namespace

#endif
