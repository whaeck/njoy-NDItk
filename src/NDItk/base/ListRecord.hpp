#ifndef NJOY_NDITK_LISTRECORD
#define NJOY_NDITK_LISTRECORD

// system includes
#include <optional>

// other includes
#include "NDItk/base/Record.hpp"

namespace njoy {
namespace NDItk {
namespace base {

/**
 *  @brief An NDI record with a list of values
 */
template < typename Derived, typename Type >
class ListRecord : protected Record {

  /* fields */
  std::optional< std::vector< Type > > values_;

protected:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] keyword   the keyword of the record
   */
  ListRecord( std::string keyword ) :
      Record( std::move( keyword ) ), values_( std::nullopt ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] keyword   the keyword of the record
   *  @param[in] value     the values of the record
   */
  ListRecord( std::string keyword, std::vector< Type > values ) :
      Record( std::move( keyword ) ), values_( std::move( values ) ) {}

public:

  using Record::keyword;

  /**
   *  @brief Return the record content
   */
  const std::optional< std::vector< Type > >& content() const {

    return this->values_;
  }

  /**
   *  @brief Return the record content
   */
  std::optional< std::vector< Type > >& content() { return this->values_; }

  /**
   *  @brief Print the record (if it has content)
   *
   *  Printing the data contained in the record is delegated to the
   *  derived class which knows how to format the data.
   *
   *  @param[in] iter   the current position in the output
   */
  template< typename OutputIterator >
  void print( OutputIterator& iter ) const {

    if ( this->content().has_value() ) {

      Record::print( iter );
      static_cast< const Derived* >( this )->write( iter );
    }
  };
};

} // base namespace
} // NDItk namespace
} // njoy namespace

#endif
