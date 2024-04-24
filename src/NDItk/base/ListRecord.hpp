#ifndef NJOY_NDITK_LISTRECORD
#define NJOY_NDITK_LISTRECORD

// system includes
#include <optional>

// other includes
#include "tools/std20/views.hpp"
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
  std::vector< Type > values_;

protected:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] keyword   the keyword of the record
   */
  ListRecord( std::string keyword ) :
      Record( std::move( keyword ) ), values_() {}

  /**
   *  @brief Constructor
   *
   *  @param[in] keyword   the keyword of the record
   *  @param[in] value     the values of the record
   */
  ListRecord( std::string keyword, std::vector< Type > values ) :
      Record( std::move( keyword ) ), values_( std::move( values ) ) {}

  /**
   *  @brief Return the record data
   */
  std::vector< Type >& data() { return this->values_; }

  /**
   *  @brief Return the record data
   */
  const std::vector< Type >& data() const { return this->values_; }

public:

  using Record::keyword;

  /**
   *  @brief Return the record values
   */
  auto values() const {

    return this->values_ | njoy::tools::std20::views::all;
  }

  /**
   *  @brief Return the size of the record
   */
  std::size_t size() const {

    return this->values_.size();
  }

  /**
   *  @brief Return whether or not the record is empty
   */
  bool empty() const { return this->size() == 0; }

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
};

} // base namespace
} // NDItk namespace
} // njoy namespace

#endif
