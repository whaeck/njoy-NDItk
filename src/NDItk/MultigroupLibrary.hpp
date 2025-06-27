#ifndef NJOY_NDITK_MULTIGROUPLIBRARY
#define NJOY_NDITK_MULTIGROUPLIBRARY

#include "MultigroupTable.hpp"
#include "base/Library.hpp"

namespace njoy {
namespace NDItk {

/**
 *  @brief A library containing multigroup tables
 */
class MultigroupLibrary : protected base::Library< MultigroupTable > {

  /* type aliases */
  using Base = base::Library< MultigroupTable >;

public:

  using Base::Base;

  using Base::numberTables;
  using Base::header;
  using Base::tables;
  using Base::getTable;
  using Base::hasTable;
  using Base::read;
  using Base::print;
};

} // namespace NDItk
} // namespace njoy

#endif