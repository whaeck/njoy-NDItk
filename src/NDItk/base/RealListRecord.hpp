#ifndef NJOY_NDITK_REALLISTRECORD
#define NJOY_NDITK_REALLISTRECORD

// system includes
#include <vector>
#include <sstream>
#include <iomanip>

// other includes
#include "tools/disco/FreeFormatReal.hpp"
#include "NDItk/base/ListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace base {

/**
 *  @brief An NDI base record with a list of real values
 */
class RealListRecord : protected ListRecord< RealListRecord, double > {

  friend class ListRecord< RealListRecord, double >;
  using Parent = ListRecord< RealListRecord, double >;

protected:

  /* auxiliary functions */

  #include "NDItk/base/RealListRecord/src/write.hpp"

  using Parent::key;

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] keyword   the keyword of the record
   */
  RealListRecord( Keyword keyword ) :
      ListRecord( std::move( keyword ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] keyword   the keyword of the record
   *  @param[in] value     the value of the record
   */
  RealListRecord( Keyword keyword, std::vector< double > value ) :
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

  #include "NDItk/base/RealListRecord/src/read.hpp"
};

} // base namespace
} // NDItk namespace
} // njoy namespace

#endif
