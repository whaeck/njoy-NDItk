#ifndef NJOY_NDITK_FROMFILE
#define NJOY_NDITK_FROMFILE

// system includes
#include <string>
#include <fstream>

// other includes
#include "tools/Log.hpp"

namespace njoy {
namespace NDItk {

  /**
   *  @brief Utility function to read the content of a file to a string
   *
   *  @param[in] filename   the file name
   */
  inline auto readContentFromFile( const std::string& filename ) {

    std::string content;
    std::ifstream in( filename,
                      std::ios::in | std::ios::binary | std::ios::ate );
    if ( not in ) {

      Log::error( "Could not open file \'{}\'", filename );
      throw std::exception();
    }

    const auto file_size = in.tellg();
    in.seekg( 0, std::ios::beg );
    content.resize( file_size / sizeof( char ) );
    in.read( content.data(), file_size );
    return content;
  }

  /**
   *  @brief Factory function to make an NDI table from a file
   *
   *  If this function is applied to a concatenated NDI file, only the first
   *  table is read.
   *
   *  @param[in] filename   the file name
   */
  template < typename Table >
  Table fromFile( const std::string& filename ) {

    std::string content = readContentFromFile( filename );

    auto iter = content.begin();
    auto end = content.end();

    // read over the first line of the file
    while ( ! *iter == '\n' ) {

      ++iter;
    }

    Table table;
    table.read( iter, end );
    return table;
  }

} // NDItk namespace
} // njoy namespace

#endif
