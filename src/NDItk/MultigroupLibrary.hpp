#ifndef NJOY_NDITK_MULTIGROUPLIBRARY
#define NJOY_NDITK_MULTIGROUPLIBRARY

#include "MultigroupTable.hpp"
#include "base/Library.hpp"

namespace njoy {
namespace NDItk {

/**
 *  @brief A library containing multigroup tables
 */
class MultigroupLibrary : public base::Library< MultigroupTable > {

    using Base = base::Library< MultigroupTable >;

public:

    using Base::Base;

};

} // namespace NDItk
} // namespace njoy

#endif 