#ifndef NJOY_NDITK_BASE_COLUMNDATA
#define NJOY_NDITK_BASE_COLUMNDATA

// system includes

// other includes
#include "tools/std23/views.hpp"
#include "NDItk/base/SubListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace base {

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
/**
 *  @brief 
 */
template< typename T, int ncol >
class ColumnData : protected base::SubListRecord< ColumnData<T,ncol>, T > {

  friend class base::SubListRecord< ColumnData<T,ncol>, T >;
  using Parent = base::SubListRecord< ColumnData<T,ncol>, T >;

public:

  ColumnData() = default;

  using Parent::Parent;

  /**
   *  @brief 
   */
  auto getColumn( int index ) const {

    if ( index > ncol ) {
      // error out
    }

    return this->values( index, this->size() ) | njoy::tools::std23::views::stride( ncol );
  }

  using Parent::values;
  using Parent::size;
  using Parent::empty;
  using Parent::begin;
  using Parent::end;
  using Parent::print;
};

} // base namespace
} // NDItk namespace
} // njoy namespace

#endif

