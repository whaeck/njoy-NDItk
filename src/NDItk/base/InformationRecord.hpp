#ifndef NJOY_NDITK_BASE_INFORMATIONRECORD
#define NJOY_NDITK_BASE_INFORMATIONRECORD

// system includes
#include <optional>

// other includes
#include "NDItk/base/Record.hpp"

namespace njoy {
namespace NDItk {
namespace base {

/**
 *  @brief An NDI base record with a single information string
 */
class InformationRecord : protected Record {

  /* fields */
  std::string information_;

public:

  /* constructor */

  /**
   *  @brief Default constructor
   */
  InformationRecord() : Record( Keyword( "info" ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] weights    the flux weights
   */
  InformationRecord( std::string information ) :
      Record( Keyword( "info" ) ), information_( std::move( information ) ) {}

  /**
   *  @brief Return the record data
   */
  const std::string& line() const { return this->information_; }

  using Record::keyword;

  /**
   *  @brief Return whether or not the record is empty
   */
  bool empty() const { return this->information_.size() == 0; }

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
      for ( auto c : this->line() ) { *iter++ = c; }
      *iter++ = '\n';
    }
  }

  /**
   *  @brief Read the record data
   *
   *  @param[in] iter    the current position in the input
   *  @param[in] end     the end position in the input
   */
  template< typename Iterator >
  void read( Iterator& iter, const Iterator& end ) {

    while ( ( iter != end ) && ( *iter != '\n' ) ) {

      ++iter;
    }
    ++iter;
    auto pos = std::find_if( iter, end, [] ( auto&& character )
                                           { return character == '\n'; } );
    this->information_ = std::string( iter, pos );
    if ( pos != end ) {

      iter = pos + 1;
    }
  };
};

} // base namespace
} // NDItk namespace
} // njoy namespace

#endif
