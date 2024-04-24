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
 *  @brief An NDI base record with a single value
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

  /**
   *  @brief Return the record data
   */
  const std::optional< Type >& data() const { return this->value_; }

  /**
   *  @brief Return the record data
   */
  std::optional< Type >& data() { return this->value_; }

  /**
   *  @brief Return whether or not the record is empty
   */
  bool empty() const { return ! this->value_.has_value(); }

  /**
   *  @brief Print the record (if it is not empty)
   *
   *  Printing the data contained in the record is delegated to the
   *  derived class which knows how to format the data.
   *
   *  @param[in] iter   the current position in the output
   */
  template< typename OutputIterator >
  void print( OutputIterator& iter ) const {

    if ( ! this->empty() ) {

      Record::print( iter );
      static_cast< const Derived* >( this )->write( iter );
    }
  };

  using Record::keyword;
};

} // base namespace
} // NDItk namespace
} // njoy namespace

#endif
