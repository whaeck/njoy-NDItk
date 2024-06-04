#ifndef NJOY_NDITK_TOFILE
#define NJOY_NDITK_TOFILE

// system includes
#include <string>
#include <fstream>

// other includes
#include "tools/Log.hpp"

namespace njoy {
namespace NDItk {

  /**
   *  @brief Function to write an NDI table to a file
   *
   *  @param[in] filename   the file name
   */
  template < typename Table >
  void toFile( const Table& table, const std::string& filename ) {

    std::string content;
    auto output = std::back_inserter( content );
    table.print( output );

    std::ofstream out( filename );
    out << "ndi: multigroup version=2.0" << std::endl;
    out << content;
    out.close();
  }

} // NDItk namespace
} // njoy namespace

#endif
