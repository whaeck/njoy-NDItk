#ifndef NJOY_NDITK_RECORDBASE
#define NJOY_NDITK_RECORDBASE

// system includes
#include <vector>
#include <string>
#include <istream>
#include <stdexcept>
#include <iostream>
// other includes


namespace njoy {
namespace NDItk {

namespace base {

template < typename Derived >
class RecordBase {

std::vector<double> data_;

  protected:

   #include "NDItk/base/RecordBase/src/read.hpp"
 

    /* constructor */
    #include "NDItk/base/RecordBase/src/ctor.hpp"

public: 

const std::vector<double>& data() const {
    return this->data_;
}

std::vector<double>& data() {
    return this->data_;
}

    std::string keyword() const {

      return static_cast< const Derived* >( this )->name();
    }
    
   #include "NDItk/base/RecordBase/src/write.hpp"
 
};

} // base namespace
} // NDItk namespace
} // njoy namespace


#endif 