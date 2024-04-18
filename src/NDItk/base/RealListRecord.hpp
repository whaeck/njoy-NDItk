#ifndef NJOY_NDITK_REALLISTRECORD
#define NJOY_NDITK_REALLISTRECORD

// system includes
#include <vector>
#include <sstream>
#include <iomanip>

// other includes
#include "tools/disco/FreeFormatReal.hpp"
#include "NDItk/base/ListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace base {

/**
 *  @brief An NDI record with a list of real values
 */
class RealListRecord : protected ListRecord< RealListRecord, double > {

  friend class ListRecord< RealListRecord, double >;
  using Parent = ListRecord< RealListRecord, double >;

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

    auto full = this->content().value().size() / 4;
    auto partial = this->content().value().size() - full * 4;
    auto x = this->content().value().begin();

    while ( full-- ) {

      buffer << std::setw( 20 ) << std::setprecision( 15 ) << std::right << x[0];
      buffer << std::setw( 20 ) << std::setprecision( 15 ) << std::right << x[1];
      buffer << std::setw( 20 ) << std::setprecision( 15 ) << std::right << x[2];
      buffer << std::setw( 20 ) << std::setprecision( 15 ) << std::right << x[3] << '\n';
      x += 4;
    }

    if ( partial ) {

      while ( partial-- ) {

        buffer << std::setw( 20 ) << std::setprecision( 15 ) << std::right << *x;
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
  RealListRecord( std::string keyword ) :
      ListRecord( std::move( keyword ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] keyword   the keyword of the record
   *  @param[in] value     the value of the record
   */
  RealListRecord( std::string keyword, std::vector< double > value ) :
      ListRecord( std::move( keyword ), std::move( value ) ) {}

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
  void read( Iterator& iter, const Iterator& end, std::size_t size ) {

    std::vector< double > data;
    data.reserve( size );
    while ( size-- ) {

      data.push_back( njoy::tools::disco::FreeFormatReal::read< double >( iter, end ) );
    }
    this->content() = data;
  };
};

} // base namespace
} // NDItk namespace
} // njoy namespace

#endif
