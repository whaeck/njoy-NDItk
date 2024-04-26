#ifndef NJOY_NDITK_PYTHON_READ
#define NJOY_NDITK_PYTHON_READ

// system includes
#include <string>

// other includes
#include "tools/Log.hpp"
#include "tools/disco/FreeFormatCharacter.hpp"

/**
 *  @brief Read a record from a string
 *
 *  @param[in] string   the string to read from
 */
template < typename Record, typename... Arguments >
Record read( const std::string& string, Arguments... arguments ) {

  using namespace njoy::tools;

  Record record;
  auto iter = string.begin();
  auto end = string.end();

  std::string key = disco::FreeFormatCharacter::read< std::string >( iter, end );
  if ( record.keyword() == key ) {

    //! @todo take into account _0 style keys
    record.read( iter, end, arguments... );

    //! @todo verify the string is now empty
    return record;
  }
  else {

    Log::error( "The record keyword is not the one expected" );
    Log::info( "Expected: \'{}\'", record.keyword() );
    Log::info( "Found: \'{}\'", key );
    throw std::exception();
  }
}

#endif
