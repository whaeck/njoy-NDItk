#ifndef NJOY_NDITK_DOSIMETRYLIBRARY
#define NJOY_NDITK_DOSIMETRYLIBRARY

#include "DosimetryTable.hpp"
#include "base/Library.hpp"

namespace njoy {
namespace NDItk {

/**
 *  @brief A library containing dosimetry tables
 */
class DosimetryLibrary : protected base::Library< DosimetryTable > {

  /* type aliases */
  using Base = base::Library< DosimetryTable >;

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