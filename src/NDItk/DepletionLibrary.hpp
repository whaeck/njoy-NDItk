#ifndef NJOY_NDITK_DEPLETIONLIBRARY
#define NJOY_NDITK_DEPLETIONLIBRARY

#include "DepletionTable.hpp"
#include "base/Library.hpp"

namespace njoy {
namespace NDItk {

/**
 *  @brief A library containing depletion tables
 */
class DepletionLibrary : protected base::Library< DepletionTable > {

  /* type aliases */
  using Base = base::Library< DepletionTable >;

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