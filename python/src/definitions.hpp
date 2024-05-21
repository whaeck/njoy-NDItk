#ifndef NJOY_NDITK_PYTHON_DEFINITIONS
#define NJOY_NDITK_PYTHON_DEFINITIONS

// system includes
#include <complex>

// other includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "tools/views/views-python.hpp"
#include "NDItk/fromFile.hpp"

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
    "Read an ACE table from a file\n\n"
    "An exception is raised if something goes wrong while reading the\n"
    "table\n\n"
    "Arguments:\n"
    "    filename    the file name and path"
  );
}

#endif
