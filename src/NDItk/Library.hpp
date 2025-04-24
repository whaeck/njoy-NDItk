#ifndef NJOY_NDITK_LIBRARY
#define NJOY_NDITK_LIBRARY

// system includes
#include <type_traits>
#include <string>
#include <vector>

// other includes
// msw: should I include these and make an assertion on the template type? 
#include "MultigroupTable.hpp"
#include "DepletionTable.hpp"
#include "tools/disco/FreeFormatCharacter.hpp"

namespace njoy {
namespace NDItk {

/**
 *  @brief A Library class that holds one or more NDI tables
 */
template< typename Table >
class Library {

  static_assert(
       std::is_same_v<Table, NDItk::MultigroupTable> 
    or std::is_same_v<Table, NDItk::DepletionTable>
  );

protected:

  /* fields */

  std::string header_;

  std::vector<Table> tables_;

public:

  #include "NDItk/Library/src/ctor.hpp"

  /**
   *  @brief Return the number of data tables in the library
   */
  auto numberTables() const { return this->tables_.size(); };

  /**
   *  @brief Return the header in the library
   */
  auto header() const { return this->header_; };

  /**
   *  @brief Return the vector of tables in the library
   */
  auto const& tables() const { return this->tables_; };

  #include "NDItk/Library/src/read.hpp"
  #include "NDItk/Library/src/print.hpp"
};

} // NDItk namespace
} // njoy namespace

#endif
