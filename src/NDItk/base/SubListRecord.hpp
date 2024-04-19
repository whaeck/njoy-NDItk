#ifndef NJOY_NDITK_BASE_SUBLISTRECORD
#define NJOY_NDITK_BASE_SUBLISTRECORD

// system includes
#include <vector>
#include <optional>

// other includes
#include "tools/Log.hpp"
#include "tools/std20/views.hpp"

namespace njoy {
namespace NDItk {
namespace base {

/**
 *  @class
 *  @brief The base class for a subrecord from an NDI file
 */
template < typename Derived, typename Type >
class SubListRecord {

public:

  using Iterator = typename std::vector< Type >::const_iterator;

private:

  /* fields */
  std::optional< std::vector< Type > > values_;
  Iterator begin_;
  Iterator end_;
  std::size_t length_;

protected:

  /* auxiliary functions */

  /* constructor */
  #include "NDItk/base/SubListRecord/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Check whether or not this record owns the data
   */
  bool owner() const { return this->values_.has_value(); }

  /**
   *  @brief Return the begin iterator to the data of the record
   */
  auto begin() const { return this->begin_; }

  /**
   *  @brief Return the end iterator to the data of the record
   */
  auto end() const { return this->end_; }

  /**
   *  @brief Return the length of the the xss array of the block
   */
  std::size_t length() const { return this->length_; }

  /**
   *  @brief Return an iterator to a data element
   *
   *  @param[in] index   the index
   */
  Iterator iterator( std::size_t index ) const {

    return std::next( this->begin(), index );
  }

  /**
   *  @brief Return the data of the record
   */
  auto values() const {

    return nano::ranges::subrange( this->begin(), this->end() );
  }

  /**
   *  @brief Return a value from the data
   *
   *  @param[in] index   the index
   */
  const Type& value( std::size_t index ) const {

    return *std::next( this->begin(), index );
  }

  /**
   *  @brief Return a subrange of a given length from the data of the record
   *
   *  @param[in] index    the index
   *  @param[in] length   the length of the subrange
   */
  auto values( std::size_t index, std::size_t length ) const {

    const auto left = this->iterator( index );
    const auto right = length > 0 ? this->iterator( index + length )
                                  : left;
    return nano::ranges::subrange( left, right );
  }

public:

  /**
   *  @brief Return whether or not the record has content
   */
  bool hasContent() const { return this->begin_ != this->end_; }

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

    if ( this->hasContent() ) {

      static_cast< const Derived* >( this )->write( iter );
    }
  };
};

} // base namespace
} // NDItk namespace
} // njoy namespace

#endif
