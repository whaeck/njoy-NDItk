#ifndef NJOY_NDITK_BASE_LIBRARY
#define NJOY_NDITK_BASE_LIBRARY

// system includes
#include <string>
#include <vector>

// other includes
#include "tools/disco/FreeFormatCharacter.hpp"

namespace njoy {
namespace NDItk {
namespace base {

/**
 *  @brief A Library class that holds one or more NDI tables
 */
template< typename Table >
class Library {

protected:

  /* fields */

  std::string header_;

  std::vector<Table> tables_;

public:

  #include "NDItk/base/Library/src/ctor.hpp"

  /**
   *  @brief Return the number of data tables in the library
   */
  auto numberTables() const { return this->tables_.size(); };

  /**
   *  @brief Return the header in the library
   */
  const std::string& header() const { return this->header_; };

  /**
   *  @brief Return the vector of tables in the library
   */
  const std::vector<Table>& tables() const { return this->tables_; };

  /**
   *  @brief Return the table in the library with the associated index
   *
   *  @param[in] index  the 0-based index of the table in the library file
   */
  const Table& getTable( int index ) const { return this->tables()[index]; };

  /**
   *  @brief Return the table in the library with the associated zaid
   *
   *  @param[in] zaid  the zaid string of the table in the library file
   */
  const Table&  getTable( const std::string& zaid ) const {

    auto pos = std::find_if( this->tables().begin(),
                             this->tables().end(),
                             [&zaid] ( const Table& table ) {

                               return table.metadata().zaid() == zaid;
                             } );
    if ( pos != this->tables().end() ) {

        return *pos;
    }
    Log::error( "The requested zaid \'{}\' has no associated record", zaid );
    throw std::exception();
  }

  /**
   *  @brief Check if there is a table in the library with the associated zaid
   *
   *  @param[in] zaid  the zaid string of the table in the library file
   */
  bool hasTable( const std::string& zaid ) const {

    auto pos = std::find_if( this->tables().begin(),
                             this->tables().end(),
                             [&zaid] ( const Table& table ) {

                               return table.metadata().zaid() == zaid;
                             } );
    if ( pos != this->tables().end() ) {

        return true;
    }
    return false;
  }

  #include "NDItk/base/Library/src/read.hpp"
  #include "NDItk/base/Library/src/print.hpp"
};

} // namespace base
} // NDItk namespace
} // njoy namespace

#endif
