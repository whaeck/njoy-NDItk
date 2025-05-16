#ifndef NJOY_NDITK_THERMONUCLEAR_SECONDARYDISTRIBUTION
#define NJOY_NDITK_THERMONUCLEAR_SECONDARYDISTRIBUTION

// system includes

// other includes
#include "NDItk/base/Record.hpp"
#include "NDItk/thermonuclear/ColumnData.hpp"
#include "NDItk/thermonuclear/InterpolationRegions.hpp"

namespace njoy {
namespace NDItk {
namespace thermonuclear {

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
/**
 *  @brief 
 */
class EnergyDistribution {

  /* fields */

  InterpolationRegions regions_;

  ColumnData<double, 2> distribution_;

public:

  EnergyDistribution() = default;

  /**
  *  @brief 
  */
  auto energies() const { return this->distribution_.getColumn(0); }

  /**
  *  @brief 
  */
  auto probabilities() const { return this->distribution_.getColumn(1); }
};

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
/**
 *  @brief 
 */
class SecondaryDistribution : protected base::Record {

  /* fields */

  InterpolationRegions regions_;

  std::vector<double> temperatures_;

  ColumnData<EnergyDistribution, 1> distribution_;

  /* auxiliary functions */

public:

  /* constructor */

  #include "NDItk/thermonuclear/SecondaryDistribution/src/ctor.hpp"

  /* methods */

  /**
   *  @brief 
   */

  using base::Record::keyword;

  #include "NDItk/thermonuclear/SecondaryDistribution/src/read.hpp"
};

} // thermonuclear namespace
} // NDItk namespace
} // njoy namespace

#endif

