#ifndef NJOY_NDITK_TOFILE
#define NJOY_NDITK_TOFILE

// system includes
#include <string>
#include <fstream>

// other includes
#include "tools/Log.hpp"
#include "NDItk/base/Library.hpp"

namespace njoy {
namespace NDItk {

  /**
   *  @brief Function to write an NDI library to a file
   *
   *  Note: this can also be used for printing an NDI table to a
   *        file, although this function is not intended for
   *        that purpose.
   *
   *  @param[in] filename   the file name
   */
  template< typename Library >
  void toFile( const Library& library, const std::string& filename ) {

    std::string content;
    auto output = std::back_inserter( content );
    library.print( output );

    std::ofstream out( filename );
    out << content;
    out.close();
  }

} // NDItk namespace
} // njoy namespace

#endif
