#ifndef NJOY_NDITK_MULTIGROUP_INTERPOLATIONREGIONS 
#define NJOY_NDITK_MULTIGROUP_INTERPOLATIONREGIONS 

// system includes
#include <sstream>
#include <iomanip>

// other includes
#include "tools/std23/views.hpp"
#include "NDItk/base/SubListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace thermonuclear {

/**
 *  @brief 
 */
class InterpolationRegions : protected base::SubListRecord< InterpolationRegions, int > {

  friend class base::SubListRecord< InterpolationRegions, int >;
  using Parent = base::SubListRecord< InterpolationRegions, int >;

  /* auxiliary functions */

  #include "NDItk/thermonuclear/InterpolationRegions/src/verify.hpp"
  #include "NDItk/thermonuclear/InterpolationRegions/src/write.hpp"

public:

  /* constructor */

  #include "NDItk/thermonuclear/InterpolationRegions/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of interpolation regions
   */
  auto numberRegions() const { return this->value( 0 ); }

  /**
   *  @brief Return a region's interpolation type 
   *
   *  @param[in] index  the interpolation region's 0-based index 
   */
  auto interpolationType( int index ) const { 

    this->verify( index );   

    return this->value( 1 + 2*index + 1 ); 
  }

  /**
   *  @brief Return the 0-based index signifying the inclusive end of a region's data
   *
   *  @param[in] index  the interpolation region's 0-based index 
   */
  auto regionEndIndex( int index ) const { 
    
    this->verify( index ); 

    return this->value( 1 + 2*index ) - 1; 
  }

  /**
   *  @brief Return the 0-based index signifying the inclusive start of a region's data
   *
   *  @param[in] index  the interpolation region's 0-based index 
   */
  auto regionBeginIndex( int index ) const { 

    return ( (index == 0) ? 0 : this->regionEndIndex( index-1 ) + 1 );
  }

  /**
   *  @brief Return the iterator for the end of a region's data
   *
   *  @param[in] index  the interpolation region's 0-based index 
   */
  auto regionEndIterator( int index ) const { 
    
    return this->iterator( this->regionEndIndex( index ) );
  }

  /**
   *  @brief Return the iterator for the start of a region's data
   *
   *  @param[in] index  the interpolation region's 0-based index 
   */
  auto regionBeginIterator( int index ) const { 

    return this->iterator( this->regionBeginIndex( index ) );
  }

  /**
   *  @brief Return the total size of a region's data
   *
   *  @param[in] index  the interpolation region's 0-based index 
   */
  auto regionSize( int index ) const { 

    return ( this->regionEndIndex( index ) - this->regionBeginIndex( index ) + 1 );
  }

  /**
   *  @brief Return a region's data
   *
   *  @param[in] index  the interpolation region's 0-based index 
   */
  auto regionData( int index ) const {

    return njoy::tools::std20::ranges::subrange( this->regionBeginIterator( index ), 
                                                 this->regionEndIterator( index ) );
  }

  using Parent::values;
  using Parent::size;
  using Parent::empty;
  using Parent::begin;
  using Parent::end;
  using Parent::print;
};

} // thermonuclear namespace
} // NDItk namespace
} // njoy namespace

#endif
