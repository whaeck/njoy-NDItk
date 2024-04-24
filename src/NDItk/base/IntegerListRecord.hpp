#ifndef NJOY_NDITK_INTEGERLISTRECORD
#define NJOY_NDITK_INTEGERLISTRECORD

// system includes
#include <vector>
#include <sstream>
#include <iomanip>

// other includes
#include "tools/disco/FreeFormatInteger.hpp"
#include "NDItk/base/ListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace base {

/**
 *  @brief An NDI base record with a list of integer values
 */
class IntegerListRecord : protected ListRecord< IntegerListRecord, int > {

  friend class ListRecord< IntegerListRecord, int >;
  using Parent = ListRecord< IntegerListRecord, int >;

protected:

  #include "NDItk/base/IntegerListRecord/src/write.hpp"

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] keyword   the keyword of the record
   */
  IntegerListRecord( std::string keyword ) :
      ListRecord( std::move( keyword ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] keyword   the keyword of the record
   *  @param[in] value     the value of the record
   */
  IntegerListRecord( std::string keyword, std::vector< int > value ) :
      ListRecord( std::move( keyword ), std::move( value ) ) {}

  /* methods */

  using Parent::keyword;
  using Parent::values;
  using Parent::size;
  using Parent::empty;
  using Parent::print;

  #include "NDItk/base/IntegerListRecord/src/read.hpp"
};

} // base namespace
} // NDItk namespace
} // njoy namespace

#endif
