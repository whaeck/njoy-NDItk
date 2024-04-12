#ifndef NJOY_NDITK_MULTIGROUP_WEIGHTS
#define NJOY_NDITK_MULTIGROUP_WEIGHTS

// system includes
// other includes
#include "NDItk/base/RecordBase.hpp"


namespace njoy {
namespace NDItk {

namespace multigroup {

class Weights: protected base::RecordBase <Weights> {

friend class base:: RecordBase <Weights>;
public: 

    /* constructor */
    #include "NDItk/multigroup/Weights/src/ctor.hpp"



    std:: string name() const{

      return "wgts";
    }

    const std::vector<double>& weights() const 
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