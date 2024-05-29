#ifndef NJOY_NDITK_STRINGLISTRECORD
#define NJOY_NDITK_STRINGLISTRECORD

// system includes
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

// other includes
#include "tools/disco/FreeFormatCharacter.hpp"
#include "NDItk/base/ListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace base {

/**
 *  @brief An NDI base record with a list of string values
 */
class StringListRecord : protected ListRecord< StringListRecord, std::string > {

  friend class ListRecord< StringListRecord, std::string >;
  using Parent = ListRecord< StringListRecord, std::string >;

protected:

  #include "NDItk/base/StringListRecord/src/write.hpp"

  using Parent::key;

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] keyword   the keyword of the record
   */
  StringListRecord( Keyword keyword ) :
      ListRecord( std::move( keyword ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] keyword   the keyword of the record
   *  @param[in] value     the value of the record
   */
  StringListRecord( Keyword keyword, std::vector< std::string > value ) :
      ListRecord( std::move( keyword ), std::move( value ) ) {}

  /* methods */

  using Parent::keyword;
  using Parent::subtype;
  using Parent::particle;
  using Parent::values;
  using Parent::size;
  using Parent::empty;
  using Parent::begin;
  using Parent::end;
  using Parent::print;

  #include "NDItk/base/StringListRecord/src/read.hpp"
};

} // base namespace
} // NDItk namespace
} // njoy namespace

#endif
