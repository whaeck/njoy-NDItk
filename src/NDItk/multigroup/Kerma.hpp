#ifndef NJOY_NDITK_MULTIGROUP_ENERGYBOUNDS
#define NJOY_NDITK_MULTIGROUP_ENERGYBOUNDS

// system includes
// other includes
#include "NDItk/base/RecordBase.hpp"


namespace njoy {
namespace NDItk {

namespace multigroup {

class EnergyBounds: protected base::RecordBase <EnergyBounds> {

friend class base:: RecordBase <EnergyBounds>;
public: 

    /* constructor */
    #include "NDItk/multigroup/EnergyBounds/src/ctor.hpp"



    std:: string name() const{

      return "e_bounds";
    }

    const std::vector<double>& bounds() const 
    {
      return this -> data();
    }

    std::size_t numberGroups() const
    {
      return this ->data().size()-1;
    }

  using RecordBase::keyword;
  using RecordBase::write;

};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace


#endif 