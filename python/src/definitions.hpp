#ifndef NJOY_NDITK_PYTHON_DEFINITIONS
#define NJOY_NDITK_PYTHON_DEFINITIONS

// system includes
#include <complex>

// other includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "tools/views/views-python.hpp"
#include "NDItk/fromFile.hpp"
#include "NDItk/toFile.hpp"

namespace python = pybind11;

/**
 *  @brief Add standard subrecord definitions
 *
 *  This adds the following standard properties:
 *    - values, size, empty
 *
 *  This adds the following standard functions:
 *    - to_string()
 *
 *  @param[in] record   the record to which the definitions have to be added
 */
template < typename Record, typename Range, typename PythonClass >
void addStandardSubrecordDefinitions( PythonClass& subrecord ) {

  subrecord
  .def_property_readonly(

    "values",
    [] ( const Record& self ) -> Range
       { return self.values(); },
    "The data values of the subrecord"
  )
  .def_property_readonly(

    "size",
    [] ( const Record& self ) { return self.size(); },
    "The size of the subrecord"
  )
  .def_property_readonly(

    "empty",
    [] ( const Record& self ) { return self.empty(); },
    "Flag indicating whether or not the subrecord is empty"
  )
  .def(

    "to_string",
    [] ( const Record& self ) -> std::string {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      self.print( output );
      return buffer;
    },
    "Return the string representation of the subrecord\n\n"
    "Arguments:\n"
    "    self    the subrecord"
  );
}

/**
 *  @brief Add standard record definitions
 *
 *  This adds the following standard properties:
 *    - keyword, values, size, empty
 *
 *  This adds the following standard functions:
 *    - to_string()
 *
 *  @param[in] record   the record to which the definitions have to be added
 */
template < typename Record, typename Range, typename PythonClass >
void addStandardRecordDefinitions( PythonClass& record ) {

  record
  .def_property_readonly(

    "keyword",
    [] ( const Record& self ) { return self.keyword(); },
    "The record keyword"
  )
  .def_property_readonly(

    "values",
    [] ( const Record& self ) -> Range
       { return self.values(); },
    "The data values of the record"
  )
  .def_property_readonly(

    "size",
    [] ( const Record& self ) { return self.size(); },
    "The size of the record"
  )
  .def_property_readonly(

    "empty",
    [] ( const Record& self ) { return self.empty(); },
    "Flag indicating whether or not the record is empty"
  )
  .def(

    "to_string",
    [] ( const Record& self ) -> std::string {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      self.print( output );
      return buffer;
    },
    "Return the string representation of the record\n\n"
    "Arguments:\n"
    "    self    the record"
  );
}

/**
 *  @brief Add standard record definitions
 *
 *  This adds the following standard properties:
 *    - keyword
 *
 *  This adds the following standard functions:
 *    - to_string()
 *
 *  @param[in] record   the record to which the definitions have to be added
 */
template < typename Record, typename PythonClass >
void addBaseRecordDefinitions( PythonClass& record ) {

  record
  .def_property_readonly(

    "keyword",
    [] ( const Record& self ) { return self.keyword(); },
    "The record keyword"
  )
  .def(

    "to_string",
    [] ( const Record& self ) -> std::string {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      self.print( output );
      return buffer;
    },
    "Return the string representation of the record\n\n"
    "Arguments:\n"
    "    self    the record"
  );
}

/**
 *  @brief Add standard table definitions
 *
 *  This adds the following standard functions:
 *    - from_file()
 *
 *  @param[in] table   the table to which the definitions have to be added
 */
template < typename Table, typename PythonClass >
void addStandardTableDefinitions( PythonClass& table ) {

  table
  .def_static(

    "from_file",
    [] ( const std::string& filename ) -> Table {

      return njoy::NDItk::fromFile< Table >( filename );
    },
    "Read an NDI table from a file\n\n"
    "An exception is raised if something goes wrong while reading the\n"
    "table\n\n"
    "Arguments:\n"
    "    filename    the file name and path"
  );
}

/**
 *  @brief Add standard library definitions
 *
 *  This adds the following standard functions:
 *    - from_file()
 *    - to_file()
 *    - number_tables()
 *    - header()
 *    - tables()
 *    - get_table(string)
 *    - get_table(int)
 *    - has_table(string)
 *
 *  @param[in] library   the library to which the definitions have to be added
 */
template < typename Library, typename PythonClass >
void addStandardLibraryDefinitions( PythonClass& library ) {

  library
  .def_static(

    "from_file",
    [] ( const std::string& filename ) -> Library {

      return njoy::NDItk::fromFile< Library >( filename );
    },
    "Read an NDI library from a file\n\n"
    "An exception is raised if something goes wrong while reading the\n"
    "library\n\n"
    "Arguments:\n"
    "    filename    the file name and path"
  )
  .def(

    "to_file",
    [] ( const Library& self, const std::string& filename ) {

      return njoy::NDItk::toFile( self, filename );
    },
    "Write an NDI library to a file\n\n"
    "Arguments:\n"
    "    self        the library\n"
    "    filename    the file name and path"
  )
  .def_property_readonly(

    "number_tables",
    [] ( const Library& self ) -> decltype(auto) {

      return self.numberTables();
    },
    "Return the number of data tables in the library"
  )
  .def_property_readonly(

    "header",
    [] ( const Library& self ) -> decltype(auto) {

      return self.header();
    },
    "Return the header in the library"
  )
  .def_property_readonly(

    "tables",
    [] ( const Library& self ) -> decltype(auto) {

      return self.tables();
    },
    "Return a vector of tables in the library"
  )
  .def(

    "get_table",
    [] ( const Library& self, int index ) -> decltype(auto) {

      return self.getTable( index );
    },
    python::arg( "index" ),
    "Return the table in the library with the associated zaid\n\n"
    "Arguments:\n"
    "    self       the library\n"
    "    index      the 0-based index of the table in the library file"
  )
  .def(

    "get_table",
    [] ( const Library& self, const std::string& zaid ) -> decltype(auto) {

      return self.getTable( zaid );
    },
    python::arg( "zaid" ),
    "Return the table in the library with the associated zaid\n\n"
    "Arguments:\n"
    "    self       the library\n"
    "    zaid       the zaid string of the table in the library file"
  )
  .def(

    "has_table",
    [] ( const Library& self, const std::string& zaid ) -> decltype(auto) {

      return self.hasTable( zaid );
    },
    python::arg( "zaid" ),
    "Check if there is a table in the library with the associated zaid\n\n"
    "Arguments:\n"
    "    self       the library\n"
    "    zaid       the zaid string of the table in the library file"
  );
}

#endif
