#ifndef NJOY_NDITK_DEPLETIONLIBRARY
#define NJOY_NDITK_DEPLETIONLIBRARY

#include "DepletionTable.hpp"
#include "base/Library.hpp"

namespace njoy {
namespace NDItk {

/**
 *  @brief A library containing depletion tables
 */
class DepletionLibrary : public base::Library< DepletionTable > {

    using Base = base::Library< DepletionTable >;

public:

    using Base::Base;
};

} // namespace NDItk
} // namespace njoy

#endif 