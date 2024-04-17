#ifndef NJOY_NDITK_SINGLEVALUERECORD
#define NJOY_NDITK_SINGLEVALUERECORD

// system includes
#include <optional>

// other includes
#include "NDItk/base/Record.hpp"

namespace njoy {
namespace NDItk {
namespace base {

/**
 *  @brief An NDI record with a single value
 */
template < typename Derived, typename Type >
class SingleValueRecord : protected Record {

  /* fields */
  std::optional< Type > value_;

protected:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] keyword   the keyword of the record
   */
  SingleValueRecord( std::string keyword ) :
      Record( std::move( keyword ) ), value_( std::nullopt ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] keyword   the keyword of the record
   *  @param[in] value     the value of the record
   */
  SingleValueRecord( std::string keyword, Type value ) :
      Record( std::move( keyword ) ), value_( std::move( value ) ) {}

public:

  using Record::keyword;

  /**
   *  @brief Return the record content
   */
  const std::optional< Type >& content() const { return this->value_; }

  /**
   *  @brief Return the record content
   */
  std::optional< Type >& content() { return this->value_; }

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
