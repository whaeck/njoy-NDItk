#ifndef NJOY_NDITK_MULTIGROUP_CROSSSECTION
#define NJOY_NDITK_MULTIGROUP_CROSSSECTION

// system includes
#include <sstream>
#include <iomanip>

// other includes
#include "NDItk/base/SubListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief A cross section record
 */
class CrossSection : protected base::SubListRecord< CrossSection, double > {

  friend class base::SubListRecord< CrossSection, double >;
  using Parent = base::SubListRecord< CrossSection, double >;

  /* fields */

  static std::vector< double > generateData( int reaction, double qvalue, std::vector< double > values ) {

    std::vector< double > data( std::move( values ) );
    data.insert( data.begin(), qvalue );
    data.insert( data.begin(), static_cast< double >( reaction ) );
    return data;
  }

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

    auto x = this->begin();
    buffer << "    " << x[0] << ' ' << std::setprecision( 15 ) << x[1] << '\n';
    x += 2;

    auto full = this->numberGroups() / 5;
    auto partial = this->numberGroups() - full * 5;

    while ( full-- ) {

      buffer << "    " << std::setprecision( 15 ) << x[0];
      buffer << ' ' << std::setprecision( 15 ) << x[1];
      buffer << ' ' << std::setprecision( 15 ) << x[2];
      buffer << ' ' << std::setprecision( 15 ) << x[3];
      buffer << ' ' << std::setprecision( 15 ) << x[4] << '\n';
      x += 5;
    }

    if ( partial ) {

      buffer << "   ";
      while ( partial-- ) {

        buffer << ' ' << std::setprecision( 15 ) << *x;
        ++x;
      }
      buffer << '\n';
    }

    for ( auto c : buffer.str() ) { *iter++ = c; }
  };

public:

  /**
   *  @brief Constructor
   *
   *  @param[in] reaction   the reaction number
   *  @param[in] qvalue     the q value
   *  @param[in] values     the cross section values
   */
  CrossSection( int reaction, double qvalue, std::vector< double > values ) :
    Parent( generateData( reaction, qvalue, std::move( values ) ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin    the begin iterator of the cross section
   *  @param[in] end      the end iterator of the cross section
   */
  CrossSection( Iterator begin, Iterator end ) :
    Parent( begin, end ) {}

  int reaction() const { return static_cast< int >( std::round( this->value( 0 ) ) ); }
  double qvalue() const { return this->value( 1 ); }
  auto crossSections() const { return this->values( 2, this->numberGroups() ); }

  int numberGroups() const { return this->length() - 2; }

  using Parent::begin;
  using Parent::end;
  using Parent::hasContent;
  using Parent::print;
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
